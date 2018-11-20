% chatbot.pl

:- use_module(library('http/http_client')).
:- use_module(library('http/http_json')).
:- use_module(library('http/json')).
:- use_module(library('http/json_convert')).

:- consult([alice]).

:- dynamic(key/2).

category([
	pattern([star(_),my,name,is,star(A)]),
	template([think(recorda('name',A)),hello,A,',',my,name,is,beerbot,'&',i,am,here,to,help,you,find,the,beer,for ,you])
]).

category([
	pattern([star(_),hello,star(_)]),
	template([hello,',',my,name,is,beerbot,'&',i,am,here,to,help,you,find,the,beer,for ,you])
]).

category([
	pattern([star(_),beer,star(_),random,star(_)]),
    template([think(randomBeer('random',A,B)),think(recorda('beer',A)),'I can recommend The ',B])
]).

category([
	pattern([star(_),random,star(_),beer,star(_)]),
   template([think(randomBeer('random',A,B)),think(recorda('beer',A)),'I can recommend The ',B])
]).

category([
	pattern([star(_),last,star(_),beer,star(_)]),
   template([(think(recorded('beer',A))),think(getDetails(A,Name,Desc,Abv,Ibu,Style)),'your last beer was The:',Name])
]).


%category([
	%pattern([star(_),find,a,star(A),style,beer,star(_)]),
    %template([(think(styleRequest(A))),(think(assert(key(A)))),
	         %'sure!',think(nl),
	         %'i found this:',think(nl)])
		% 'Name:',Name,think(nl)])
%]).


category([

       pattern([star(_),details,star(_)]),
       that(['I can recommend The ',star(_)]),
       template([sure,think(nl),
		  (think(recorded('beer',A)))
		  ,think(getDetails(A,Name,Desc,Abv,Ibu,Style)),
		 'Name:',Name,think(nl),
		 'Style:',Style,think(nl),
		 'Description:',Desc,think(nl),
		 'alcohol:',Abv,'%',think(nl),
		 'Ibu:',Ibu])
]).

category([
	pattern([star(_),what,star(_),ibu,star(_)]),
    template(['IBU is an abbreviation for the International Bitterness Units scale, a gauge of beer''s bitterness. '])
]).


category([
	pattern([who,is,alan,turing,'?']),
	template(['Alan Mathison Turing',was,a,'British',mathematician,',',logician,',',cryptanalyst,',',philosopher,',',computer,scientist,',',mathematical,biologist,',',and,marathon,and,ultra,distance,runner,'.'])
]).

category([
	pattern([star(_),like,star(Style),style,star(_)]),
	template([think(recorda('pref',Style)),'i''ll remember that you like',Style])
]).

category([
	pattern([star(_),style,do,i,like,star(_),?]),
	template(['your preffered style is:',think(recorded('pref',Style)),Style])
]).

category([
	pattern([can,you,give,me,star(A),'?']),
	template(['I couln''t find',A,'for you, my apologies'])
]).


category([
	pattern([star(_),thank,you,star(_)]),
	template(['you''re very welcome',think(recorded('name',Name)),Name])
]).

category([
	pattern([star(_),bye,star(_)]),
	template(['Goodbye,',think(recorded('name',Name)),Name])
]).


category([
	pattern([star(_)]),
	template(['Sorry, i think something went wrong'])
]).


randomBeer(EP,Beer,Name) :-
	Baseurl ='http://sandbox-api.brewerydb.com/v2/beer/',
	Endpoint = EP,
	Token = '?key=09efce9fb4c53d25e1d4ea888225fa71' ,
	atomic_concat(Baseurl,Endpoint,Buffer),
        atomic_concat(Buffer,Token,Final),
	http_get(Final,json(Json),[]),
	member(data=json(B),Json),
	member(id=Beer,B),
	member(name=Name,B).

getDetails(EP,Name,Desc,Abv,Ibu,Style):-
	Baseurl ='http://sandbox-api.brewerydb.com/v2/beer/',
	print(EP),
	Endpoint = EP,
	Token = '/?key=09efce9fb4c53d25e1d4ea888225fa71',
        atomic_concat(Baseurl,Endpoint,Buffer),
	atomic_concat(Buffer,Token,Final),
	http_get(Final,json(Json),[]),
	member(data=json(D),Json),
	%member(id=EP,D),
	member(name=Name,D),
	member(description=Desc,D),
	member(abv=Abv,D),
	member(ibu=Ibu,D),
        member(style=json(S),D),
	member(category=json(C),S),
	member(name=Style,C).

%styleRequest(EP,Name):-
       %atomic_list_concat(EP,'',End),
       %Baseurl = 'http://sandbox-api.brewerydb.com/v2/styles/',
       %Endpoint = End,
       %Token = '?key=09efce9fb4c53d25e1d4ea888225fa71',
       %atomic_concat(Baseurl,Endpoint,Buffer),
       %atomic_concat(Buffer,Token,Final),
       %atomic_concat(Baseurl,Token,Final),
       %print(Final),
       %http_get(Final,json(Json),[]),
       %member(data=json(D),Json),
       %print('test'),
       %EP is D,
       %readJson(D).
      % member(object=Test,D),
       %member(id=EP,D),
      % member(name=Name,D).

%readJson([]).
%readJson([H|T]):-
	%print(H),
	%printName(H),readJson(T).

%printName(H):-
	%member(name=Name,H),
%	print(H.name).
