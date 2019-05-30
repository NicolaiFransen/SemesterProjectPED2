% Optimization course, Aalborg University, by Erik Lund & Henrik Clemmensen Pedersen
% Golden section search implementation - follows recipe in 
% Arora (2016) pp. 437-440 (Arora (2012) pp. 425-429, Arora (2004) pp. 289-291)

function [alpha, f_alpha, iter] = GoldenSection(FUNC, delta, epsilonGS, nMaxGSIter)


  % Input: FUNC: the name of the function f(alpha) to call
  %        delta: the increment used in the initial bracketing process
  %        epsilonGS: the convergence criterion to use in the golden section search
  %        nMaxGSIter: maximum number of iterations in the golden section search
  % Output: alpha: the value of alpha at the minimum
  %         f_alpha: the function value at the minimum
   
  G = (-1+sqrt(5))/2; % G = 0.618034;  % The golden section
  % Phase 1:  Determine the initial interval bracketing a minimum

  % Initial bracketing is used to find the interval containing alpha^*.
  % We use a sequence of larger increments based on the golden ratio.
  % We will store values of alpha and f(alpha) for each iteration,
  % and as Matlab only allows positive indices of vectors, the indices are
  % different than the ones in Arora:
  % f(1) contains f evaluated for alpha(1) = 0
  % f(2) contains f evaluated for alpha(2) = delta 
  % f(3) contains f evaluated for alpha(3) = delta + (1+G)*delta
  % f(j) contains f evaluated for alpha(j) = alpha(j-1)*(2+G)

  % Matlab is slow at reallocating data, so we start by defining 
  % the maximum sizes of f and alpha
  f(1:nMaxGSIter) = 0;     
  alpha(1:nMaxGSIter) = 0;

  % Step 1 in Arora's algorithm:
  for j=1:2
    alpha(j) = (j-1)*delta;
    f(j) = FUNC(alpha(j));
  end

  % Check that the function is not increasing initially 
  % (this may happen if delta is too big), see comments in Arora. 
  % This check is not included in Arora's algorithm.
  if (f(2) > f(1)) 
    disp('Golden section search: f(delta) > f(0)')
    disp('The value of delta is reduced until f(delta) < f(0)')
    for i = 1:nMaxGSIter
      delta = delta/10;   % We reduce delta until f(delta) < f(0)
      f(2) = FUNC(delta); 
      if (f(2) < f(1))
        alpha(2) = delta;
        sprintf('Reduced delta to %10.4E using %d iterations', delta, i)
        break
      end
    end
  end

  % We may now proceed the bracketing
  nSteps = 0;
  for j = 3:nMaxGSIter
    nSteps = nSteps + 1;
    alpha(j) = alpha(j-1) + delta*(1+G)^nSteps;
    f(j) = FUNC(alpha(j));
    if f(j) > f(j-1)
      alpha_u = alpha(j);
      alpha_l = alpha(j-2);
      alpha_a = alpha(j-1);
      f_alpha_u = f(j);
      f_alpha_l = f(j-2);
      f_alpha_a = f(j-1);            
      break;            
    end
  end

  % Phase 2:  Perform the golden section search in the initial interval
  %           determined in phase 1.

  % Step 2 in Arora's algorithm:
  I = alpha_u - alpha_l;       % Calculating initial interval of uncertainty
  alpha_b = alpha_l + G*I;     % Determining intermediate point
  f_alpha_b = FUNC(alpha_b);

  % Step 3 in Arora's algorithm:
  iteration=0;
  for i = 1:nMaxGSIter
      iteration = iteration + 1;
    if (f_alpha_a < f_alpha_b) % Arora step 3(i)
      alpha_u = alpha_b;
      f_alpha_u = f_alpha_b;
      alpha_b = alpha_a;
      f_alpha_b = f_alpha_a;
      I = alpha_u - alpha_l;
      alpha_a = alpha_l + (1-G)*I;
      f_alpha_a = FUNC(alpha_a);
    elseif (f_alpha_a > f_alpha_b) % Arora step 3(ii)
      alpha_l = alpha_a;
      f_alpha_l = f_alpha_a;
      alpha_a = alpha_b;
      f_alpha_a = f_alpha_b;
      I = alpha_u - alpha_l;
      alpha_b = alpha_l + G*I;
      f_alpha_b = FUNC(alpha_b);    
    else   % Arora step 3(iii)
      alpha_l = alpha_a;
      f_alpha_l = f_alpha_a;
      alpha_u = alpha_b;
      f_alpha_u = f_alpha_b;
      I = alpha_u - alpha_l;
      alpha_a = alpha_l + (1-G)*I;
      f_alpha_a = FUNC(alpha_a);
      alpha_b = alpha_l + G*I;
      f_alpha_b = FUNC(alpha_b);
    end
    % Step 4 in Arora's algorithm:
    % Check convergence on the interval of uncertainty: I = alpha_u - alpha_l
    if (I < epsilonGS)
      alpha = (alpha_b + alpha_a)/2;
      f_alpha = FUNC(alpha);
      iter = iteration;
      break;
    end
  end

end