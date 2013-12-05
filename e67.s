% e67.s
% ===========

output_options([c45,c45c,c45e,lp,prolog]).
%talking(4).
use_packs(0).

use_package(query).

minfreq(0.001).


warmode_key(location(-GeneA, -Loc)).
	rmode(optrans(+GeneA, -GeneB)).
	rmode(class1(+GeneA, #)).
	rmode(class1(+GeneB, #)).


typed_language(yes).
        type(location(gene, loc)).
	type(optrans(gene, gene)).
	type(class1(gene, class)).



