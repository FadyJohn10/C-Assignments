analyticalFriction file script
function f = analyticalFriction(e, D, Re)
f = 1.325 / (( log( e/(3.7*D) + 5.74/(Re^0.9) ) ))^2;
end
func file script
function g = func(f, e, D, Re)
g = 1/sqrt(f) + 2 * log10( e/(3.7*D) + 2.51/(Re*sqrt(f)) );
end
bisection file script
function [XR] = bisection(XL, XU, e, D, Re)
XR = (XL + XU)/2;
while abs(func(XL,e,D,Re)*func(XR,e,D,Re))
>= 0.001
> 0
XR = (XL + XU)/2;
if func(XL,e,D,Re)*func(XR,e,D,Re) < 0
XU = XR;
elseif func(XL,e,D,Re)*func(XR,e,D,Re)
XL = XR;
end end
end
Main file script
lower = 0.008;
upper = 0.8;
while(true)
fprintf('Choose an option from this menu: \n');
fprintf('1. calculate friction factor using analytical and numerical methods \n');
fprintf('2. conduct an analysis of how the friction factor varies with conduit diameter \n'); fprintf('3. conduct an analysis of how the friction factor varies with pipe roughness \n'); fprintf('4. conduct an analysis of ho2w the friction factor varies with fluid density \n'); fprintf('5. conduct an analysis of how the friction factor varies with dynamic viscosity \n'); fprintf('6. Exit the program \n');
choice = input('Your choice is: ');
if choice == 1
% Prompt the user to enter the parameters needed to calculate the friction factor
e = input('Enter the pipe roughness (e): '); while (e>3 || e<1e-4)
e = input('Invalid input. Enter a pipe roughness value between 1e-4 and 3: '); end
p = input('Enter the fluid density (p): '); while (p>2000 || p<0.5)
p = input('Invalid input. Enter a fluid density value between 0.5 and 2000: '); end
D = input('Enter the conduit diameter (D): ');
V = input('Enter the velocity (V): ');
mu = input('Enter the dynamic viscosity (mu): '); while (mu>300 || mu<1e-6)
mu = input('Invalid input. Enter a dynamic viscosity value between 1e-6 and 300: '); end
        Re = p*V*D/mu;
        if Re <= 4000
fprintf('The equation applies only for Re values > 4000. Program exitted \n');
break; end
fprintf('The numerical friction factor: %f\n', bisection(lower, upper, e, D, Re)); fprintf('The analytical friction factor: %f\n', analyticalFriction(e, D, Re));
elseif choice == 2
% Prompt the user to enter the parameters needed to calculate the friction factor e = input('Enter the pipe roughness (e): ');
while (e>3 || e<1e-4)
e = input('Invalid input. Enter a pipe roughness value between 1e-4 and 3: '); end
p = input('Enter the fluid density (p): '); while (p>2000 || p<0.5)
p = input('Invalid input. Enter a fluid density value between 0.5 and 2000: '); end
V = input('Enter the velocity (V): ');
mu = input('Enter the dynamic viscosity (mu): '); while (mu>300 || mu<1e-6)
mu = input('Invalid input. Enter a dynamic viscosity value between 1e-6 and 300: '); end
% Define the lower and upper values for the conduit diameter, as well as the step size.
L = input('Enter the lower value for the conduit diameter: '); H = input('Enter the upper value for the conduit diameter: ');
delta = input('Enter the step size for the conduit diameter: ');
D = L:delta:H; % Create a vector of conduit diameters using the L, H, and delta values defined above. f_analytic = zeros(length(D));
f_numerical = zeros(length(D));
        for i = 1:length(D)
            Re = p.*V.*D(i)./mu;
            if(Re <= 4000)
fprintf('Re value should be > 4000.. program exitted \n');
return; end
f_analytic(i) = analyticalFriction(e, D(i), Re); % Calculate the friction factor for each conduit diameter using the analytical equation.
f_numerical(i) = bisection(lower, upper, e, D(i), Re); % Calculate the friction factor for each conduit diameter using the numerical equation.
end
plot(D, f_analytic, '-r.'); %plotting diameter and analytic friction factors hold on
plot(D, f_numerical, '-b.'); %plotting diameter and numerical friction factors %Editing the graph format
xlabel('Conduit diameter (D)'); ylabel('Friction factor (f)');
title('Friction factor vs. conduit diameter'); legend({'Analytical', 'Numerical'});
hold off
saveas(graph,'friction_factor_vs_diameter.png'); %saving the graph with png extension
elseif choice == 3
% Prompt the user to enter the parameters needed to calculate the friction factor D = input('Enter the conduit diameter (D): ');
p = input('Enter the fluid density (p): ');
while (p>2000 || p<0.5)
p = input('Invalid input. Enter a fluid density value between 0.5 and 2000: '); end
V = input('Enter the velocity (V): ');
mu = input('Enter the dynamic viscosity (mu): '); while (mu>300 || mu<1e-6)
mu = input('Invalid input. Enter a dynamic viscosity value between 1e-6 and 300: '); end
% Define the lower and upper values for the pipe roughness, as well as the step size.
L = input('Enter the lower value for the pipe roughness: ');
H = input('Enter the upper value for the pipe roughness: '); delta = input('Enter the step size for the pipe roughness: ');
e = L:delta:H; % Create a vector of pipe roughness using the L, H, and delta values defined above. f_analytic = zeros(length(e));
f_numerical = zeros(length(e));
Re = p.*V.*D./mu;
        if(Re <= 4000)
                fprintf('Re
return; end
f_numerical(i) = bisection(lower, upper, e(i), D, Re); % Calculate the friction factor for each pipe roughness using the numerical equation.
end
plot(e, f_analytic, '-r.'); %plotting pipe roughness and analytic friction factors hold on
plot(e, f_numerical, '-b.'); %plotting pipe roughness and numerical friction factors %Editing the graph format
xlabel('Pipe roughness (e)'); ylabel('Friction factor (f)'); title('Friction factor vs. pipe roughness'); legend({'Analytical', 'Numerical'});
hold off
saveas(graph,'friction_factor_vs_pipe_roughness.png'); %saving the graph with png extension
elseif choice == 4
% Prompt the user to enter the parameters needed to calculate the friction factor e = input('Enter the pipe roughness (e): ');
while (e>3 || e<1e-4)
e = input('Invalid input. Enter a pipe roughness value between 1e-4 and 3: '); end
D = input('Enter the conduit diameter (D): ');
V = input('Enter the velocity (V): ');
mu = input('Enter the dynamic viscosity (mu): '); while (mu>300 || mu<1e-6)
mu = input('Invalid input. Enter a dynamic viscosity value between 1e-6 and 300: '); end
% Define the lower and upper values for the fluid density, as well as the step size.
L = input('Enter the lower value for the fluid density: ');
value should be > 4000.. program exitted \n');
analyticalFriction(e(i), D, Re); % Calculate the friction factor for each pipe roughness using the analytical equation.
for i = 1:length(e)
    f_analytic(i) =

H = input('Enter the upper value for the fluid density: '); delta = input('Enter the step size for the fluid density: ');
p = L:delta:H; % Create a vector of fluid density using the L, H, and delta values defined above. f_analytic = zeros(length(p));
f_numerical = zeros(length(p));
        for i = 1:length(p)
            Re = p(i).*V.*D./mu;
            if(Re <= 4000)
fprintf('Re value should be > 4000.. program exitted \n');
return; end
f_analytic(i) = analyticalFriction(e, D, Re); % Calculate the friction factor for each fluid density using the analytical equation.
f_numerical(i) = bisection(lower, upper, e, D, Re); % Calculate the friction factor for each fluid density using the numerical equation.
end
plot(p, f_analytic, '-r.'); %plotting fluid density and analytic friction factors hold on
plot(p, f_numerical, '-b.'); %plotting fluid density and numerical friction factors %Editing the graph format
xlabel('Fluid density (p)');
ylabel('Friction factor (f)');
title('Friction factor vs. fluid density');
legend({'Analytical', 'Numerical'});
hold off
saveas(graph,'friction_factor_vs_fluid _density.png'); %saving the graph with png extension
elseif choice == 5
% Prompt the user to enter the parameters needed to calculate the friction factor e = input('Enter the pipe roughness (e): ');
while (e>3 || e<1e-4)
e = input('Invalid input. Enter a pipe roughness value between 1e-4 and 3: '); end
D = input('Enter the conduit diameter (D): '); V = input('Enter the velocity (V): ');
p = input('Enter the fluid density (p): '); while (p>2000 || p<0.5)
p = input('Invalid input. Enter a fluid density value between
0.5 and 2000: ');
well as the step size.
end
% Define the lower and upper values for the dynamic viscosity, as
L = input('Enter the lower value for the dynamic viscosity: ');
H = input('Enter the upper value for the dynamic viscosity: '); delta = input('Enter the step size for the dynamic viscosity: ');
mu = L:delta:H; % Create a vector of dynamic viscosity using the L, H, and delta values defined above. f_analytic = zeros(length(mu));
f_numerical = zeros(length(mu));
        for i = 1:length(mu)
            Re = p.*V.*D./mu(i);
            if(Re <= 4000)
fprintf('Re value should be > 4000.. program exitted \n');
return; end
f_analytic(i) = analyticalFriction(e, D, Re); % Calculate the friction factor for each dynamic viscosity using the analytical equation.
f_numerical(i) = bisection(lower, upper, e, D, Re); % Calculate the friction factor for each dynamic viscosity using the numerical equation.
end
plot(mu, f_analytic, '-r.'); %plotting dynamic viscosity and analytic friction factors hold on
plot(mu, f_numerical, '-b.'); %plotting dynamic viscosity and numerical friction factors %Editing the graph format
xlabel('Dynamic viscosity (mu)'); ylabel('Friction factor (f)');
title('Friction factor vs. dynamic viscosity'); legend({'Analytical', 'Numerical'});
hold off
saveas(graph,'friction_factor_vs_dynamic_viscosity.png'); %saving the graph with png extension
elseif choice == 6
fprintf('You exitted the program... \n'); break;
else
fprintf('Invalid option...'); end
end
