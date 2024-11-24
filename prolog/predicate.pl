% Define facts
male(jake).
male(john).
male(mike).
female(mary).
female(susan).
female(anna).

parent(jake, mary).
parent(jake, john).
parent(susan, mary).
parent(susan, john).
parent(john, mike).
parent(anna, mike).

% Define rules
is_parent(X) :- parent(X, _).
is_child(X) :- parent(_, X).
father(X, Y) :- male(X), parent(X, Y).
mother(X, Y) :- female(X), parent(X, Y).
is_grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
is_sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
is_uncle(X, Y) :- male(X), parent(Z, Y), is_sibling(X, Z).
is_aunt(X, Y) :- female(X), parent(Z, Y), is_sibling(X, Z).

% Run some queries
% ?- male(jake).               % Expected output: true
% ?- is_parent(jake).          % Expected output: true
% ?- parent(X, mary).          % Expected output: X = jake; X = susan.
% ?- father(jake, mary).       % Expected output: true
% ?- mother(susan, john).      % Expected output: true
% ?- is_grandparent(jake, mike). % Expected output: true
% ?- is_sibling(mary, john).   % Expected output: true
% ?- is_uncle(john, mike).     % Expected output: false
% ?- is_aunt(anna, mike).      % Expected output: false

% -------------------------------------------------------------------

% Facts
% parent(john, mary).
% parent(john, tom).
% parent(mary, alice).
% parent(tom, bob).

% Rules
% grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
% isParent(X) :- parent(X, _).

% ["/filepath"].
% queries
% grandparent(john, alice).   Expected output: true
% isParent(mary).             Expected output: true
% parent(X, bob).             Expected output: X = tom
