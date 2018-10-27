function [child]=MutateGenotypes(child)
global n;
likelihood=rand;
if lt(likelihood,0.1) %%%%%%%%%%%%%%0.1i check!!
    gene=round(rand*(n-1)+1); %Generates a random gene between the first and last genes to undergo mutation.
    child(gene)=xor(child(gene),1);
end