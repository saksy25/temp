% Facts
parent(john, mary).
parent(john, tom).
parent(mary, alice).
parent(tom, bob).

% Rules
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
isParent(X) :- parent(X, _).


% ["/filepath"].
% queries
% grandparent(john, alice).   Expected output: true
% isParent(mary).             Expected output: true
% parent(X, bob).             Expected output: X = tom
