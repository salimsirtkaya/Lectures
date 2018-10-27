clear;
t=cputime;
input=[1,2,3;4,5,6;7,-1,8]

%output belirleme:
input_size=size(input);
for n=1:input_size(1)    
    output(n,:)=[((n-1)*input_size(2)+1):(n*input_size(2))];
end
output(input_size(1),input_size(2))=-1;

%succesor hesaplama:

states(:,:,1)=input;
back_pointer(1)=1;

suc=succesors(input);
suc_size=size(suc);

goal=0;
m=[];
n=[];
p=[];


[m,n,p]=size(states);
  
        

    
for a=1:100000;
  
       
        suc=succesors(states(:,:,a));
        suc_size=size(suc);     
      
        for i=1:suc_size(3);
            
            if suc(:,:,i)==output;
                                      
                               
                solution(:,:,1)=suc(:,:,i);
                bp=a
                c=2
                while bp~=1
                    
                    solution(:,:,c)=states(:,:,bp);
                    bp=back_pointer(bp);
                    c=c+1;        
                end
                
                solution(:,:,c)=states(:,:,1);
                t=cputime-t              
                break
                
            else
                
                k=0; 
                for j=1:p;
                    if suc(:,:,i) == states(:,:,j);
                        k=1;
                    end
                end
            end
            if k==0;
               states(:,:,p+1)=suc(:,:,i);
                back_pointer(p+1)=a;
                p=p+1;
                            
            end
            
        end
             
    
       
    
end
    


