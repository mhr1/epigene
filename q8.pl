%#!/usr/local/apps/swi-prolog/pl-5.6.29/bin/pl -G32m -L32m -g go -t halt >>log.txt

% Q8
% Key to model format

go:-
        %consult(yst_gene),
        consult(yst_g_chromo),
        consult(yst_g_centre),
        consult(yst_g_length),
        consult(yst_g_next),
        consult(yst_g_start),
        consult(yst_g_strand),
        consult(yst_m_cls_lvl1),
        consult(yst_m_cls_lvl2),
        consult(yst_m_cls_lvl3),
        consult(yst_m_cls_lvl4),
        consult(yst_g_gaplength),
        consult(y_hom_2),
        run(chrI),
        told,
        run(chrII),
        told,
        run(chrIII),
        told,
        run(chrIV),
        told,
	run(chrV),
        told,
        run(chrVI),
        told,
	run(chrVII),
        told,
        run(chrVIII),
        told,
	run(chrIX),
        told,
        run(chrX),
        told,
	run(chrXI),
        told,
        run(chrXII),
        told,
        run(chrXIII),
        told,
        run(chrXIV),
        told,
        run(chrXV),
        told,
        run(chrXVI),
        told,
        tell(user),
	nl.

run(chrI):-    tell('yst_mod_1.kb'), getGene(chrI).
run(chrII):-   tell('yst_mod_2.kb'), getGene(chrII).
run(chrIII):-  tell('yst_mod_3.kb'), getGene(chrIII).
run(chrIV):-   tell('yst_mod_4.kb'), getGene(chrIV).
run(chrV):-    tell('yst_mod_5.kb'), getGene(chrV).
run(chrVI):-   tell('yst_mod_6.kb'), getGene(chrVI).
run(chrVII):-  tell('yst_mod_7.kb'), getGene(chrVII).
run(chrVIII):- tell('yst_mod_8.kb'), getGene(chrVIII).
run(chrIX):-   tell('yst_mod_9.kb'), getGene(chrIX).
run(chrX):-    tell('yst_mod_10.kb'), getGene(chrX).
run(chrXI):-   tell('yst_mod_11.kb'), getGene(chrXI).
run(chrXII):-  tell('yst_mod_12.kb'), getGene(chrXII).
run(chrXIII):- tell('yst_mod_13.kb'), getGene(chrXIII).
run(chrXIV):-  tell('yst_mod_14.kb'), getGene(chrXIV).
run(chrXV):-   tell('yst_mod_15.kb'), getGene(chrXV).
run(chrXVI):-  tell('yst_mod_16.kb'), getGene(chrXVI).
%run(chrI):-   tell('yst_mod_1.kb'), getGene(chrI).
		
getGene(Chr):-
        call(query(X, Chr)),
        write('begin(model('),
        write(X),
        write(')).'), nl,
        getLocation(X),
        write('end(model('),
        write(X),
        write(')).'), nl, nl,
        fail;
        write('failed to find a gene'),
        nl.

getLocation(Gene):-
        call(centre_point(Gene, Y)),
        write('centre_point('),
        write(Y),
        write(').'), nl,
        fail;
        getLength(Gene).

getLength(Gene):-
        call(gene_length(Gene, Y)),
        write('gene_length('),
        write(Y),
        write(').'), nl,
        fail;
        getNext(Gene).

getNext(Gene):-
        call(is_next_to(Gene, Y)),
        write('is_next_to('),
        write(Y),
        write(').'), nl,
        fail;
        getStart(Gene).

getStart(Gene):-
        call(start_locus(Gene, Y)),
        write('start_locus('),
        write(Y),
        write(').'), nl,
        fail;
        getStrand(Gene).

getStrand(Gene):-
        call(strand(Gene, Y)),
        write('strand('),
        write(Y),
        write(').'), nl,
        fail;
        get_m_1(Gene).

get_m_1(Gene):-
        call(m_cls_lvl1(Gene, Y)),
        write('m_cls_lvl1('),
        write(Y),
        write(').'), nl,
        fail;
        get_m_2(Gene).

get_m_2(Gene):-
        call(m_cls_lvl2(Gene, Y)),
        write('m_cls_lvl2('),
        write(Y),
        write(').'), nl,
        fail;
        get_m_3(Gene).

get_m_3(Gene):-
        call(m_cls_lvl3(Gene, Y)),
        write('m_cls_lvl3('),
        write(Y),
        write(').'), nl,
        fail;
        get_m_4(Gene).

get_m_4(Gene):-
        call(m_cls_lvl4(Gene, Y)),
        write('m_cls_lvl4('),
        write(Y),
        write(').'), nl,
        fail;
        getGapLength(Gene).

getGapLength(Gene):-
        call(y_gap_length(Gene, Y, Z)),
        write('y_gap_length('),
        write(Y),
        write(', '),
        write(Z),
        write(').'), nl,
        fail;
        getHomology(Gene).


getHomology(Gene):-
        %Homology = arabidopsis,
        call(y_hom(Gene, Homology, Evalue)),
        write('y_hom('),
        write(Homology),
        write(', '),
        write(Evalue),
        write(').'),
        nl,
        fail;
        N = 0.

% Select chromosome
% -----------------

query(Gene, Chr):-
        chromosome(Gene, Chr).

y_hom_q(X, Y, Z):-
        y_hom(X, Y, Z),
        Z < 1e-20.    %Set Evalue threshold

writelist([], N):-
        N1 is N - 1,
	write(N1).

writelist([X|L], N):-
        write(N), tab(1),
	write(X),
	nl,
        N1 is N + 1,
        writelist(L, N1).
		
