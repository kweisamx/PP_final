clc;
da = 1000;
tol = 1e-12;
wl = 7;                                  % wanted lambdas
sd = 10;                                 % smallest dim of subspace
ld = 30;                                 % largest dim of subspace

G = rand(da,800);                     % give initial
% A = G*G';
% [~, De] = eig(A);                     
% [De, ~] = sort(abs(diag(De)), 'descend');  % for checking

Vl = zeros(da,wl);
Dl = zeros(2,wl);
U1 = randn(da,1);
U = [U1/norm(U1) zeros(da,ld)];          % U(:,31)
T = zeros(ld+1);                           % T(31,31) = beta31
% v = zeros(da,1);                         % u0 = U(:,0)
% beta0 = 0;
cl = 0;                                  % current conv lambda
restart = 0;
% cd = 0;                                % current dim of subspace

U(:,2) = G*(G'*U(:,1));
T(1,1) = U(:,1)'*U(:,2);
U(:,2) = U(:,2) - T(1,1)*U(:,1);
% v = U(:,2) - T(1,1)*U(:,1) - beta0*v;
T(2,1) = norm(U(:,2));
T(1,2) = T(2,1);
U(:,2) = U(:,2)/T(2,1);
cd = 1;
% norm(A*U(:,1:cd)-U(:,1:cd)*T(1:cd,1:cd)-T(cd+1,cd)*U(:,cd+1)*[zeros(1,cd-1) 1])

while cl < wl+1
    
    for j = cd+1: ld
        U(:,j+1) = G*(G'*U(:,j)) - T(j,j-1)*U(:,j-1);
        T(j,j) = U(:,j)'*U(:,j+1);
        U(:,j+1) = U(:,j+1) - T(j,j)*U(:,j) ;
        for k = 1: j
            gamma = U(:,k)'*U(:,j+1);
            U(:,j+1) = U(:,j+1) - gamma*U(:,k);
        end
        T(j,j) = T(j,j) + gamma;
        T(j+1,j) = norm(U(:,j+1));                   % positive number
        T(j,j+1) = T(j+1,j);
        U(:,j+1) = U(:,j+1)/T(j+1,j);
    end
    cd = ld;
    % norm(A*U(:,1:cd)-U(:,1:cd)*T(1:cd,1:cd)-T(cd+1,cd)*U(:,cd+1)*[zeros(1,cd-1) 1])

    [S, Rt] = eig(T(1:cd,1:cd));
    Rt = diag(Rt);
    abs_Rt = abs(Rt);
    [~, idxt] = sort(abs_Rt, 'descend');
    Rt = Rt(idxt);
    S = S(:,idxt);
    for j = cl+1: cd
        if T(cd+1,cd)*abs(S(cd,j)) < tol && cl < wl
            cl = cl + 1;
            Vl(:,cl) = U(:,1:cd)*S(:,j);
            Dl(:,cl) = [restart; Rt(j)];
        end
    end
    if cl == wl
        break
    end
    
    b = [zeros(cd-1,1); 1];
    for j = 1: cd-sd
        [Q, R] = qr(T(1:cd,1:cd)-Rt(cd-j+1)*eye(cd));
        T(1:cd,1:cd) = R*Q + Rt(cd-j+1)*eye(cd);
        U(:,1:cd) = U(:,1:cd)*Q;
        b = Q'*b;
    end
    U(:,sd+1) = T(sd+1,sd)*U(:,sd+1) + (T(cd+1,cd)*b(sd))*U(:,cd+1);
    T(sd+1,sd) = norm(U(:,sd+1));
    T(sd,sd+1) = T(sd+1,sd);
    U(:,sd+1) = U(:,sd+1)/T(sd+1,sd);
    cd = sd;
    restart = restart + 1;

end



