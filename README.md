## Introduction
This program is an implementation of the Runge-Kutta RK4 method and the Numerov method for solving the Schrodinger equation for a particle in a potential well to extract the wavefunction and allowed energy levels. It is part of Chapter 9 in the computational physics textbook by Landau(2015)[^1] on numerical ordinary differential eqautions.

[^1]: Landau, R. H.(2015). Computational physics problem solving with python. John Wiley & Sons, Incorporated.

## Schrodinger Equation

The time independent Schrodinger equation is an ordinary differential equation of the form<br/>

$$\frac{d^2\psi}{dx^2}+\frac{2m}{\hbar^2}V(x)\psi(x)=\frac{2m}{\hbar^2}E\psi(x)$$
<br/>

Where we have the potential function $V(x)$, the wavefunction $\psi(x)$ and energy level $E$ which we are trying to find here. We denote $\frac{2m}{\hbar^2}E$ as $\kappa^2$ from now on for ease of notation. In this case, assuming V(x) describes a finite square potential with the form <br/>

$$V(x)= \begin{cases}
-V_0 & |x|<a\\
0 & |x|\geq a
\end{cases}$$
<br/>

where $V_0$ is the depth of the well and $2a$ is the width of the well. The challenge of solving this is that the particle becomes bounded within the well. Because of this, we have to establish boundary conditions when solving the equation. In this case the boundary conditions are that the wavefunction vanish far from the potential well or<br/>

$$\psi(x)\to e^{-\kappa^2x},\ x\to\infty$$
<br/>

$$\psi(x)\to e^{\kappa^2x},\ x\to-\infty$$
<br/>

## Solving Method
To establish this ode with boundary conditions, we combine our choice of ode solver with a searching method such as the bijection method to find the allowed energy level. Essentially we use two ode solvers with starting points from the left and right end away from the well and solve inwards towards the potential well. We then minimize the log derivative of the meeting point of both solved wave equations to find the best value for the allowed energy level.<br/>
<br/>
The log derivative is given by<br/>

$$\triangle = \frac{\psi'_\text{left}/\psi_\text{left}-\psi'_\text{right}/\psi_\text{right}}{\psi'_\text{left}/\psi_\text{left}+\psi'_\text{right}/\psi_\text{right}}$$
## Numerov Method

## Program Example