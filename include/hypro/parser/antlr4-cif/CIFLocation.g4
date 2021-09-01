/*exported from CIF3 Sytax*/
grammar CIFLocation;
import Expressions;

locations:			location+;

location: 			'location' ';' 					# loc
				| 'location' identifier ';'			# locId
				| 'location' ':' locationElements		# locElem
				| 'location' identifier ':' locationElements	# locIdElem
				;

locationElements: 		locationElement+;

locationElement: 		'initial' ';'					# locElemInitialFlag
				| 'initial' expressions ';'			# locElemInitialFlagExpr
				| invariantDecls				# locElemInv
				| 'equation' equations ';'			# locElemEqs
				| 'marked' ';'					# locElemMarked
				| 'marked' expressions ';'			# locElemMarkedExpr
				| 'urgent' ';'					# locElemUrgent
				| 'edge' coreEdge 'goto' identifier ';'		# locElemEdgeTo
				| 'edge' coreEdge ';'				# locElemLoop
				;

coreEdge: 			edgeEvents optEdgeGuard optEdgeUrgent optEdgeUpdate
				| 'when' expressions optEdgeUrgent optEdgeUpdate
				| 'now' optEdgeUpdate
				| 'do' updates;

optEdgeGuard: 			('when' expressions)?;

optEdgeUrgent: 			'now'?;

optEdgeUpdate: 			('do' updates)?;

edgeEvents: 			edgeEvent (',' edgeEvent)*;

edgeEvent: 			'tau'
				| name
				| name '!'
				| name '!' expression
				| name '?';

invariantDecls: 		optSupKind 'invariant' invariants ';'
				| supKind invariants ';' ;

invariants: 			invariant (',' invariant)*;

invariant: 			expression					# invExpr
				| name 'needs' expression			# invNeeds
				| nonEmptySetExpression 'needs' expression	# invNeedsSet
				| expression 'disables' name			# invDisables
				| expression 'disables' nameSet			# invDisablesSet
				;

updates: 			update (',' update)*;

update: 			adressable ':=' expression						# updateNonIf
				| 'if' expressions ':' updates optElifUpdates optElseUpdate 'end'	# updateIf
				;	

optElifUpdates: 		('elif' expressions ':' updates)*;

optElseUpdate: 			('else' update)?;

adressables: 			adressable (',' adressable)*;

adressable: 			identifier					# adressableId
				| identifier projections			# adressableProj
				| '(' adressable ',' adressable ')'		# adressablePair
				;

projections: 			projection*;

projection: 			'[' expression ']';
