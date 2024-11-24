% Facts: Define diseases with their associated symptoms
disease(flu, [cough, fever, headache]).
disease(cold, [cough, runny_nose]).
disease(migraine, [headache, fatigue]).
disease(allergy, [sneezing, runny_nose, itchy_eyes]).
disease(food_poisoning, [vomiting, weakness, fever, stomach_ache]).

% Rule to identify diseases based on given symptoms
diagnose(Symptoms, Disease) :-
    disease(Disease, DiseaseSymptoms),
    subset(DiseaseSymptoms, Symptoms).

% Helper predicate to check if one list is a subset of another
 subset([], _).
 subset([H|T], List) :-
    member(H, List),
    subset(T, List).



% ?- diagnose([cough, fever, headache], Disease).   Disease = flu.
% ?- diagnose([cough, runny_nose, fever], Disease).   Disease = cold ;   Disease = flu.
