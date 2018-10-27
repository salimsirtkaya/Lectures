% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
% Simulation of the K-team K213 linear camera turret
function response=kiks_turret_k213(tcommand,targs)
global KIKS_SIM_LINVIS_RP KIKS_MMPERPIXEL KIKS_K213_STEP KIKS_K213_NONORMALIZE KIKS_502500 KIKS_SIM_LINVIS_LMIN KIKS_SIM_LINVIS_LMAX KIKS_RBT_TIME KIKS_SIM_LINVIS_LL KIKS_SIM_LINVIS_IMG KIKS_SIM_LINVIS_RP KIKS_SIM_LINVIS_LU KIKS_ROBOT_MATRIX KIKS_WALL_WIDTH KIKS_WALL_RENDER KIKS_ARENA_MASK KIKS_ARENA_COLORMASK;

if nargin<2
    % return the turret id
    response=2;
    return;
end;

switch tcommand
    case 'B' % turret software version
        response=[sprintf('t,2,b,1,0')];
    case {'N','M','O','P','Q','R','S','T','L'} % read image
        response=kiks_turret_k213_main(tcommand,targs);
    case 'U' % set reading period
        switch args(1)
            case 0
                KIKS_SIM_LINVIS_RP(port)=0.2;
            case 1
                KIKS_SIM_LINVIS_RP(port)=0.05;
            case 2
                KIKS_SIM_LINVIS_RP(port)=0.1;
            case 3
                KIKS_SIM_LINVIS_RP(port)=0.15;
            case 4
                KIKS_SIM_LINVIS_RP(port)=0.25;
            case 5
                KIKS_SIM_LINVIS_RP(port)=0.5;
            case 6
                KIKS_SIM_LINVIS_RP(port)=1;
            case 7
                KIKS_SIM_LINVIS_RP(port)=5;
        end;
        response=['u'];
    otherwise
        response=['z,Protocol error'];
end;

function imgstr=kiks_turret_k213_main(tcmd,targs)
global KIKS_K213_NOISE KIKS_K213_NONORMALIZE KIKS_MMPERPIXEL KIKS_K213_STEP KIKS_502500 KIKS_SIM_LINVIS_LMIN KIKS_SIM_LINVIS_LMAX KIKS_RBT_TIME KIKS_SIM_LINVIS_LL KIKS_SIM_LINVIS_IMG KIKS_SIM_LINVIS_RP KIKS_SIM_LINVIS_LU KIKS_ROBOT_MATRIX KIKS_WALL_WIDTH KIKS_WALL_RENDER KIKS_ARENA_MASK KIKS_ARENA_COLORMASK;

id = 1;
wc=245; % white color value
bc=50; % black color value
res=ones(1,64)*127;
img=res;
minlen=50; % mm
maxlen=500; % mm
step=10;

switch tcmd
    case {'N','L'}
        interval=1;
        colres=1;
        subimg=0;
        startpx=1;
    case 'M'
        interval=1;
        colres=2;
        subimg=0;
        startpx=1;
    case 'Q'
        interval=1;
        colres=1;
        subimg=8;
        startpx=targs(1);
    case 'R'
        interval=1;
        colres=1;
        subimg=16;
        startpx=targs(1);
    case 'S'   
        interval=2;
        colres=1;
        subimg=0;
        startpx=1;
    case 'T'
        interval=4;
        colres=1;
        subimg=0;
        startpx=1;
end;

angs=[18:-36/65:-18];
if subimg>0
    endpx=startpx+subimg-1;
else
    endpx=64;
end;

%for px=startpx:interval:endpx
sincelast=KIKS_RBT_TIME(id)-KIKS_SIM_LINVIS_LU(id);
if (sincelast>=KIKS_SIM_LINVIS_RP(id)) 
    % | (KIKS_SIM_LINVIS_LMIN(id)>startpx) | (KIKS_SIM_LINVIS_LMAX(id)<endpx) | (KIKS_SIM_LINVIS_LINT(id)>interval)
    KIKS_SIM_LINVIS_LU(id)=KIKS_RBT_TIME(id);
    xs=(KIKS_ROBOT_MATRIX(id,1,1)+5*sin(KIKS_ROBOT_MATRIX(id,1,3)+pi))/KIKS_MMPERPIXEL;
    ys=(KIKS_ROBOT_MATRIX(id,1,2)+5*cos(KIKS_ROBOT_MATRIX(id,1,3)+pi))/KIKS_MMPERPIXEL;
    [ysz,xsz]=size(KIKS_ARENA_COLORMASK);
    bpx=zeros(1,64);
    for px=1:64
        ang=(angs(px)/(180/pi))+KIKS_ROBOT_MATRIX(id,1,3);
        cosang=cos(ang);
        sinang=sin(ang);
        xvals=round(KIKS_502500*cosang+xs);
        yvals=round(-KIKS_502500*sinang+ys);
        % isolate values that are within boundaries
        ok=find(xvals>=1 & xvals<=xsz & yvals>=1 & yvals<=ysz);
        xok=xvals(ok);
        yok=yvals(ok);
        %      plot(xok-KIKS_WALL_WIDTH+KIKS_WALL_RENDER,yok-KIKS_WALL_WIDTH+KIKS_WALL_RENDER);
        idx=((xok-1)*ysz+yok);
        obst=find(KIKS_ARENA_COLORMASK(idx)); % get all non-zero elements
        if ~isempty(obst)
            dist=min(obst);
            
            xp=xvals(dist);
            yp=yvals(dist);
            c=KIKS_ARENA_COLORMASK(yp,xp);
            oldc=c;
            back=0;
            
            while (c>0 & back<KIKS_K213_STEP/KIKS_MMPERPIXEL)
                back=back+1;
                oldc=c;
                xp=xp-cosang;
                yp=yp+sinang;
                c=KIKS_ARENA_COLORMASK(floor(yp),floor(xp));
            end;
            c=oldc;
            
            res(px)=bc+c*(wc-bc)/255;            
            img(px)=res(px);
        else
            % no color data for this pixel (out of reach)
            bpx(px)=1;
            % keep stepping until we hit something
            dy=-sinang*KIKS_K213_STEP;
            dx=cosang*KIKS_K213_STEP;
            sx=xvals(end);
            sy=yvals(end);
            c=0;
            while c==0
                sx=sx+dx;
                sy=sy+dy;
                c=KIKS_ARENA_COLORMASK(floor(sy),floor(sx));
            end;
            % back up, we don't want wrong wall color.
            dy=-sinang;
            dx=cosang;
            nc=c;
            while nc~=0
                c=nc;
                sx=sx-dx;
                sy=sy-dy;
                nc=KIKS_ARENA_COLORMASK(floor(sy),floor(sx));
            end;
            
            res(px)=bc+c*(wc-bc)/255;            
            img(px)=res(px);         
        end;      
    end;
    % Blur out-of-view pixels
    b=find(bpx);
    if ~isempty(b)
        [tmp,sz]=size(b);
        msk=[3 2 1 1 2 2 3];
        msk=msk/sum(msk);
        fimg=[img(1) img(1) img(1) img img(64) img(64) img(64)];
        for i=1:sz
            ix=b(i);
            img(ix)=fimg(ix)*msk(1)+fimg(ix+1)*msk(2)+fimg(ix+2)*msk(3)+fimg(ix+3)*msk(4)+fimg(ix+4)*msk(5)+fimg(ix+5)*msk(6)+fimg(ix+6)*msk(7);
        end;
    end;
    
    % normalize, calculate light   
    imx=double(max(img)); % ==> wc
    ime=double(mean(img));
    imn=double(min(img)); % ==> bc
    if isempty(KIKS_K213_NONORMALIZE)
        if imx<wc
            img=img+(wc-imx);
        end;
        if imn>bc
            img=img-(255-wc);
        end;
    end;
    % calculate light level
    % ime=255 ==> 100,
    % ime=1	 ==> 2600
    KIKS_SIM_LINVIS_LL(id)=round((255-imx)*7+175+rand*50)+(imx-ime);
    
    % falloff
    for px=1:64
        img(px)=img(px)+rand*20-10;
        fl=240-(abs(angs(px)))*(abs(angs(px))/18)^(1.5)*6;
        if abs(angs(px))>5 & img(px)>fl
            img(px)=fl+rand*20-10;
        end;
    end;
    % blur image
    if max(abs(KIKS_ROBOT_MATRIX(id,1,5)),abs(KIKS_ROBOT_MATRIX(id,1,6)))>0
        % blur a lot if rotating
        if KIKS_ROBOT_MATRIX(id,1,5)~=KIKS_ROBOT_MATRIX(id,1,6)
            msk=[4 3 2 1 2 3 4]; % heavy blur
        else
            msk=[1 1 1 4 1 1 1]; % medium blur
        end;
    else     
        msk=[0 0 1 2 1 0 0]; % light blur
    end;
    
    filt=filter2(msk/sum(msk),[img(1) img(1) img(1) img img(64) img(64) img(64)]);
    img=filt(4:67);  
    
    [rows,cols]=size(img);
    noiseimg=rand(rows,cols)*255;

    KIKS_SIM_LINVIS_IMG(id,:)=uint8(img*((100-KIKS_K213_NOISE)/100)+noiseimg*(KIKS_K213_NOISE/100));
end;

imgstr=sprintf('t,2,%c',lower(tcmd));
switch tcmd
    case 'N'
        for i=startpx:interval:endpx
            imgstr=[imgstr sprintf(',%d',round(KIKS_SIM_LINVIS_IMG(id,i)))];         
        end;
    case 'M'
        for i=1:31
            imgstr=[imgstr sprintf(',%d',round(round(KIKS_SIM_LINVIS_IMG(id,i)/4)+128+round(KIKS_SIM_LINVIS_IMG(id,i+1)/4)))];
        end;
    case 'O'
        [val,no]=max(KIKS_SIM_LINVIS_IMG(id,:))
        imgstr=[imgstr sprintf(',%d',round(no))];
    case 'P'
        [val,no]=min(KIKS_SIM_LINVIS_IMG(id,:))
        imgstr=[imgstr sprintf(',%d',round(no))];
    case 'Q'
        for i=startpx:interval:endpx
            if i<=64
                imgstr=[imgstr sprintf(',%d',round(KIKS_SIM_LINVIS_IMG(id,i)))];         
            else
                imgstr=[imgstr ',NaN'];
            end;
        end;
    case 'R'
        for i=startpx:interval:endpx
            if i<=64
                imgstr=[imgstr sprintf(',%d',round(KIKS_SIM_LINVIS_IMG(id,i)))];         
            else
                imgstr=[imgstr ',NaN'];
            end;
        end;  
    case 'S'
        for i=startpx:interval:endpx
            imgstr=[imgstr sprintf(',%d',round(KIKS_SIM_LINVIS_IMG(id,i)))];         
        end;  
    case 'T'
        for i=startpx:interval:endpx
            imgstr=[imgstr sprintf(',%d',round(KIKS_SIM_LINVIS_IMG(id,i)))];         
        end;  
    case 'L'
        hi=floor(KIKS_SIM_LINVIS_LL(id)/256);
        lo=KIKS_SIM_LINVIS_LL(id)-(hi*256);
        imgstr=[imgstr sprintf(',%d,%d',round(hi),round(lo))];
end;