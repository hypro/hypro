/*exported from CIF3 Sytax*/
grammar InputOutput;
import Expressions;

optIoDecls: ioDecls*;

ioDecls: svgFile
	| svgCopy
	| svgMove
	| svgOut
	| svgIn
	| printFile
	| print;

svgFile: 'svgFile' stringToken ';';

optSvgFile: ('file' stringToken)?;

svgCopy: 'svgCopy' 'id' expression optSvgCopyPre optSvgCopyPost optSvgFile ';';

optSvgCopyPre: ('pre' expression)?;

optSvgCopyPost: ('post' expression)?;

svgMove: 'svgmove' 'id' expression 'to' expression ',' expression ';'
	| 'svgmove' 'id' expression 'to' expression ',' expression ':' svgFile 'end';

svgOut: 'svgout' 'id' expression svgAttr 'value' expression optSvgFile ';';

svgAttr: 'attr' stringToken
	| 'text';

svgIn: 'svgin' 'id' expression 'event' svgInEvent optSvgFile ';';

svgInEvent: name
	| 'if' expression ':' name optSvgInEventElifs 'else' name 'end'
	| 'if' expression ':' name svgInEventElifs 'end';

optSvgInEventElifs: svgInEventElifs?;

svgInEventElifs: ('elif' expression ':' name)+;

printFile: 'printFile' stringToken ';';

print: 'print' printTxt optPrintFors optPrintWhen optPrintFile';';

printTxt: expression
	| 'pre' expression
	| 'post' expression
	| 'pre' expression 'post' expression;

optPrintFors: ('for' printFors)?;

printFors: printFor (',' printFor)*;

printFor: 'event'
	| 'time'
	| name
	| 'initial'
	| 'final';

optPrintWhen: (   'when' expression
		| 'when' 'pre' expression
		| 'when' 'post' expression
		| 'when' 'pre' expression 'post' expression)?;

optPrintFile: ('file' stringToken)?;
