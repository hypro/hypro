// Generated from HybridAutomaton.g4 by ANTLR 4.7
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class HybridAutomatonParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.7", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, T__23=24, 
		T__24=25, T__25=26, T__26=27, T__27=28, T__28=29, T__29=30, T__30=31, 
		PARALLELOTOPE=32, BOX=33, JUMP=34, DEFINE=35, IN=36, COMMENT=37, EQUALS=38, 
		BOOLRELATION=39, PLUS=40, TIMES=41, NUMBER=42, VARIABLE=43, WS=44, EXPONENTIAL=45;
	public static final int
		RULE_start = 0, RULE_vardeclaration = 1, RULE_jumps = 2, RULE_transition = 3, 
		RULE_fromto = 4, RULE_urgent = 5, RULE_guard = 6, RULE_allocation = 7, 
		RULE_resetfct = 8, RULE_aggregation = 9, RULE_term = 10, RULE_polynom = 11, 
		RULE_interval = 12, RULE_equation = 13, RULE_constraint = 14, RULE_intervalexpr = 15, 
		RULE_constrset = 16, RULE_setting = 17, RULE_fixedsteps = 18, RULE_time = 19, 
		RULE_plotsetting = 20, RULE_filename = 21, RULE_maxjumps = 22, RULE_print = 23, 
		RULE_remainder = 24, RULE_identity = 25, RULE_fixedorders = 26, RULE_cutoff = 27, 
		RULE_precision = 28, RULE_modes = 29, RULE_location = 30, RULE_activities = 31, 
		RULE_invariants = 32, RULE_init = 33, RULE_initstate = 34, RULE_unsafeset = 35, 
		RULE_badstate = 36;
	public static final String[] ruleNames = {
		"start", "vardeclaration", "jumps", "transition", "fromto", "urgent", 
		"guard", "allocation", "resetfct", "aggregation", "term", "polynom", "interval", 
		"equation", "constraint", "intervalexpr", "constrset", "setting", "fixedsteps", 
		"time", "plotsetting", "filename", "maxjumps", "print", "remainder", "identity", 
		"fixedorders", "cutoff", "precision", "modes", "location", "activities", 
		"invariants", "init", "initstate", "unsafeset", "badstate"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'hybrid reachability'", "'{'", "'}'", "'state var'", "','", "'jumps'", 
		"'urgent'", "'guard'", "'reset'", "'['", "']'", "'setting'", "'fixed steps'", 
		"'time'", "'gnuplot octagon'", "'output'", "'max jumps'", "'print'", "'remainder estimation'", 
		"'identity precondition'", "'fixed orders'", "'cutoff'", "'precision'", 
		"'modes'", "'poly ode 1'", "'poly ode 2'", "'poly ode 3'", "'linear ode'", 
		"'inv'", "'init'", "'unsafe set'", "'parallelotope aggregation'", "'box aggregation'", 
		"'->'", "':='", "'in'", null, "'='", null, "'+'", "'*'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, null, null, null, null, null, null, null, null, null, null, null, 
		null, null, null, null, null, null, null, null, null, null, null, null, 
		null, null, null, null, null, null, null, null, "PARALLELOTOPE", "BOX", 
		"JUMP", "DEFINE", "IN", "COMMENT", "EQUALS", "BOOLRELATION", "PLUS", "TIMES", 
		"NUMBER", "VARIABLE", "WS", "EXPONENTIAL"
	};
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "HybridAutomaton.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public HybridAutomatonParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class StartContext extends ParserRuleContext {
		public VardeclarationContext vardeclaration() {
			return getRuleContext(VardeclarationContext.class,0);
		}
		public SettingContext setting() {
			return getRuleContext(SettingContext.class,0);
		}
		public ModesContext modes() {
			return getRuleContext(ModesContext.class,0);
		}
		public JumpsContext jumps() {
			return getRuleContext(JumpsContext.class,0);
		}
		public InitContext init() {
			return getRuleContext(InitContext.class,0);
		}
		public UnsafesetContext unsafeset() {
			return getRuleContext(UnsafesetContext.class,0);
		}
		public StartContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_start; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterStart(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitStart(this);
		}
	}

	public final StartContext start() throws RecognitionException {
		StartContext _localctx = new StartContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_start);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(74);
			match(T__0);
			setState(75);
			match(T__1);
			setState(76);
			vardeclaration();
			setState(77);
			setting();
			setState(78);
			modes();
			setState(79);
			jumps();
			setState(80);
			init();
			setState(81);
			match(T__2);
			setState(83);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__30) {
				{
				setState(82);
				unsafeset();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VardeclarationContext extends ParserRuleContext {
		public List<TerminalNode> VARIABLE() { return getTokens(HybridAutomatonParser.VARIABLE); }
		public TerminalNode VARIABLE(int i) {
			return getToken(HybridAutomatonParser.VARIABLE, i);
		}
		public VardeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_vardeclaration; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterVardeclaration(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitVardeclaration(this);
		}
	}

	public final VardeclarationContext vardeclaration() throws RecognitionException {
		VardeclarationContext _localctx = new VardeclarationContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_vardeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(85);
			match(T__3);
			setState(86);
			match(VARIABLE);
			setState(93);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__4) {
				{
				setState(89); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(87);
					match(T__4);
					setState(88);
					match(VARIABLE);
					}
					}
					setState(91); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( _la==T__4 );
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class JumpsContext extends ParserRuleContext {
		public List<TransitionContext> transition() {
			return getRuleContexts(TransitionContext.class);
		}
		public TransitionContext transition(int i) {
			return getRuleContext(TransitionContext.class,i);
		}
		public JumpsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_jumps; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterJumps(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitJumps(this);
		}
	}

	public final JumpsContext jumps() throws RecognitionException {
		JumpsContext _localctx = new JumpsContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_jumps);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(95);
			match(T__5);
			setState(96);
			match(T__1);
			setState(100);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VARIABLE) {
				{
				{
				setState(97);
				transition();
				}
				}
				setState(102);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(103);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TransitionContext extends ParserRuleContext {
		public FromtoContext fromto() {
			return getRuleContext(FromtoContext.class,0);
		}
		public List<UrgentContext> urgent() {
			return getRuleContexts(UrgentContext.class);
		}
		public UrgentContext urgent(int i) {
			return getRuleContext(UrgentContext.class,i);
		}
		public List<GuardContext> guard() {
			return getRuleContexts(GuardContext.class);
		}
		public GuardContext guard(int i) {
			return getRuleContext(GuardContext.class,i);
		}
		public List<ResetfctContext> resetfct() {
			return getRuleContexts(ResetfctContext.class);
		}
		public ResetfctContext resetfct(int i) {
			return getRuleContext(ResetfctContext.class,i);
		}
		public List<AggregationContext> aggregation() {
			return getRuleContexts(AggregationContext.class);
		}
		public AggregationContext aggregation(int i) {
			return getRuleContext(AggregationContext.class,i);
		}
		public TransitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_transition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterTransition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitTransition(this);
		}
	}

	public final TransitionContext transition() throws RecognitionException {
		TransitionContext _localctx = new TransitionContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_transition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(105);
			fromto();
			setState(112);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__6) | (1L << T__7) | (1L << T__8) | (1L << PARALLELOTOPE) | (1L << BOX))) != 0)) {
				{
				setState(110);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case T__6:
					{
					setState(106);
					urgent();
					}
					break;
				case T__7:
					{
					setState(107);
					guard();
					}
					break;
				case T__8:
					{
					setState(108);
					resetfct();
					}
					break;
				case PARALLELOTOPE:
				case BOX:
					{
					setState(109);
					aggregation();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				setState(114);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FromtoContext extends ParserRuleContext {
		public List<TerminalNode> VARIABLE() { return getTokens(HybridAutomatonParser.VARIABLE); }
		public TerminalNode VARIABLE(int i) {
			return getToken(HybridAutomatonParser.VARIABLE, i);
		}
		public TerminalNode JUMP() { return getToken(HybridAutomatonParser.JUMP, 0); }
		public FromtoContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fromto; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterFromto(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitFromto(this);
		}
	}

	public final FromtoContext fromto() throws RecognitionException {
		FromtoContext _localctx = new FromtoContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_fromto);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(115);
			match(VARIABLE);
			setState(116);
			match(JUMP);
			setState(117);
			match(VARIABLE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class UrgentContext extends ParserRuleContext {
		public UrgentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_urgent; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterUrgent(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitUrgent(this);
		}
	}

	public final UrgentContext urgent() throws RecognitionException {
		UrgentContext _localctx = new UrgentContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_urgent);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(119);
			match(T__6);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class GuardContext extends ParserRuleContext {
		public ConstrsetContext constrset() {
			return getRuleContext(ConstrsetContext.class,0);
		}
		public GuardContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_guard; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterGuard(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitGuard(this);
		}
	}

	public final GuardContext guard() throws RecognitionException {
		GuardContext _localctx = new GuardContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_guard);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(121);
			match(T__7);
			setState(122);
			match(T__1);
			setState(123);
			constrset();
			setState(124);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AllocationContext extends ParserRuleContext {
		public TerminalNode VARIABLE() { return getToken(HybridAutomatonParser.VARIABLE, 0); }
		public TerminalNode DEFINE() { return getToken(HybridAutomatonParser.DEFINE, 0); }
		public PolynomContext polynom() {
			return getRuleContext(PolynomContext.class,0);
		}
		public IntervalContext interval() {
			return getRuleContext(IntervalContext.class,0);
		}
		public AllocationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_allocation; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterAllocation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitAllocation(this);
		}
	}

	public final AllocationContext allocation() throws RecognitionException {
		AllocationContext _localctx = new AllocationContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_allocation);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(126);
			match(VARIABLE);
			setState(127);
			match(DEFINE);
			setState(130);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case NUMBER:
			case VARIABLE:
				{
				setState(128);
				polynom();
				}
				break;
			case T__9:
				{
				setState(129);
				interval();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ResetfctContext extends ParserRuleContext {
		public List<AllocationContext> allocation() {
			return getRuleContexts(AllocationContext.class);
		}
		public AllocationContext allocation(int i) {
			return getRuleContext(AllocationContext.class,i);
		}
		public ResetfctContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_resetfct; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterResetfct(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitResetfct(this);
		}
	}

	public final ResetfctContext resetfct() throws RecognitionException {
		ResetfctContext _localctx = new ResetfctContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_resetfct);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(132);
			match(T__8);
			setState(133);
			match(T__1);
			setState(137);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VARIABLE) {
				{
				{
				setState(134);
				allocation();
				}
				}
				setState(139);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(140);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AggregationContext extends ParserRuleContext {
		public TerminalNode PARALLELOTOPE() { return getToken(HybridAutomatonParser.PARALLELOTOPE, 0); }
		public TerminalNode BOX() { return getToken(HybridAutomatonParser.BOX, 0); }
		public AggregationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_aggregation; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterAggregation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitAggregation(this);
		}
	}

	public final AggregationContext aggregation() throws RecognitionException {
		AggregationContext _localctx = new AggregationContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_aggregation);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(142);
			_la = _input.LA(1);
			if ( !(_la==PARALLELOTOPE || _la==BOX) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(143);
			match(T__1);
			setState(144);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TermContext extends ParserRuleContext {
		public List<TerminalNode> NUMBER() { return getTokens(HybridAutomatonParser.NUMBER); }
		public TerminalNode NUMBER(int i) {
			return getToken(HybridAutomatonParser.NUMBER, i);
		}
		public List<TerminalNode> VARIABLE() { return getTokens(HybridAutomatonParser.VARIABLE); }
		public TerminalNode VARIABLE(int i) {
			return getToken(HybridAutomatonParser.VARIABLE, i);
		}
		public List<TerminalNode> TIMES() { return getTokens(HybridAutomatonParser.TIMES); }
		public TerminalNode TIMES(int i) {
			return getToken(HybridAutomatonParser.TIMES, i);
		}
		public TermContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_term; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterTerm(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitTerm(this);
		}
	}

	public final TermContext term() throws RecognitionException {
		TermContext _localctx = new TermContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_term);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(146);
			_la = _input.LA(1);
			if ( !(_la==NUMBER || _la==VARIABLE) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(151);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==TIMES) {
				{
				{
				setState(147);
				match(TIMES);
				setState(148);
				_la = _input.LA(1);
				if ( !(_la==NUMBER || _la==VARIABLE) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
				}
				setState(153);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PolynomContext extends ParserRuleContext {
		public List<TermContext> term() {
			return getRuleContexts(TermContext.class);
		}
		public TermContext term(int i) {
			return getRuleContext(TermContext.class,i);
		}
		public List<TerminalNode> PLUS() { return getTokens(HybridAutomatonParser.PLUS); }
		public TerminalNode PLUS(int i) {
			return getToken(HybridAutomatonParser.PLUS, i);
		}
		public PolynomContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_polynom; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterPolynom(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitPolynom(this);
		}
	}

	public final PolynomContext polynom() throws RecognitionException {
		PolynomContext _localctx = new PolynomContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_polynom);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(154);
			term();
			setState(160);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					setState(158);
					_errHandler.sync(this);
					switch (_input.LA(1)) {
					case PLUS:
						{
						{
						setState(155);
						match(PLUS);
						setState(156);
						term();
						}
						}
						break;
					case NUMBER:
					case VARIABLE:
						{
						setState(157);
						term();
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					} 
				}
				setState(162);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IntervalContext extends ParserRuleContext {
		public List<TerminalNode> NUMBER() { return getTokens(HybridAutomatonParser.NUMBER); }
		public TerminalNode NUMBER(int i) {
			return getToken(HybridAutomatonParser.NUMBER, i);
		}
		public IntervalContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interval; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterInterval(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitInterval(this);
		}
	}

	public final IntervalContext interval() throws RecognitionException {
		IntervalContext _localctx = new IntervalContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_interval);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(163);
			match(T__9);
			setState(164);
			match(NUMBER);
			setState(165);
			match(T__4);
			setState(166);
			match(NUMBER);
			setState(167);
			match(T__10);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class EquationContext extends ParserRuleContext {
		public TerminalNode VARIABLE() { return getToken(HybridAutomatonParser.VARIABLE, 0); }
		public TerminalNode EQUALS() { return getToken(HybridAutomatonParser.EQUALS, 0); }
		public PolynomContext polynom() {
			return getRuleContext(PolynomContext.class,0);
		}
		public EquationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_equation; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterEquation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitEquation(this);
		}
	}

	public final EquationContext equation() throws RecognitionException {
		EquationContext _localctx = new EquationContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_equation);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(169);
			match(VARIABLE);
			setState(170);
			match(EQUALS);
			setState(171);
			polynom();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ConstraintContext extends ParserRuleContext {
		public List<PolynomContext> polynom() {
			return getRuleContexts(PolynomContext.class);
		}
		public PolynomContext polynom(int i) {
			return getRuleContext(PolynomContext.class,i);
		}
		public TerminalNode BOOLRELATION() { return getToken(HybridAutomatonParser.BOOLRELATION, 0); }
		public TerminalNode EQUALS() { return getToken(HybridAutomatonParser.EQUALS, 0); }
		public ConstraintContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constraint; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterConstraint(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitConstraint(this);
		}
	}

	public final ConstraintContext constraint() throws RecognitionException {
		ConstraintContext _localctx = new ConstraintContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_constraint);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(173);
			polynom();
			setState(174);
			_la = _input.LA(1);
			if ( !(_la==EQUALS || _la==BOOLRELATION) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(175);
			polynom();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IntervalexprContext extends ParserRuleContext {
		public TerminalNode VARIABLE() { return getToken(HybridAutomatonParser.VARIABLE, 0); }
		public TerminalNode IN() { return getToken(HybridAutomatonParser.IN, 0); }
		public IntervalContext interval() {
			return getRuleContext(IntervalContext.class,0);
		}
		public IntervalexprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_intervalexpr; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterIntervalexpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitIntervalexpr(this);
		}
	}

	public final IntervalexprContext intervalexpr() throws RecognitionException {
		IntervalexprContext _localctx = new IntervalexprContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_intervalexpr);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(177);
			match(VARIABLE);
			setState(178);
			match(IN);
			setState(179);
			interval();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ConstrsetContext extends ParserRuleContext {
		public List<ConstraintContext> constraint() {
			return getRuleContexts(ConstraintContext.class);
		}
		public ConstraintContext constraint(int i) {
			return getRuleContext(ConstraintContext.class,i);
		}
		public List<IntervalexprContext> intervalexpr() {
			return getRuleContexts(IntervalexprContext.class);
		}
		public IntervalexprContext intervalexpr(int i) {
			return getRuleContext(IntervalexprContext.class,i);
		}
		public ConstrsetContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constrset; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterConstrset(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitConstrset(this);
		}
	}

	public final ConstrsetContext constrset() throws RecognitionException {
		ConstrsetContext _localctx = new ConstrsetContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_constrset);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(185);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==NUMBER || _la==VARIABLE) {
				{
				setState(183);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,11,_ctx) ) {
				case 1:
					{
					setState(181);
					constraint();
					}
					break;
				case 2:
					{
					setState(182);
					intervalexpr();
					}
					break;
				}
				}
				setState(187);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class SettingContext extends ParserRuleContext {
		public List<FixedstepsContext> fixedsteps() {
			return getRuleContexts(FixedstepsContext.class);
		}
		public FixedstepsContext fixedsteps(int i) {
			return getRuleContext(FixedstepsContext.class,i);
		}
		public List<TimeContext> time() {
			return getRuleContexts(TimeContext.class);
		}
		public TimeContext time(int i) {
			return getRuleContext(TimeContext.class,i);
		}
		public List<RemainderContext> remainder() {
			return getRuleContexts(RemainderContext.class);
		}
		public RemainderContext remainder(int i) {
			return getRuleContext(RemainderContext.class,i);
		}
		public List<IdentityContext> identity() {
			return getRuleContexts(IdentityContext.class);
		}
		public IdentityContext identity(int i) {
			return getRuleContext(IdentityContext.class,i);
		}
		public List<PlotsettingContext> plotsetting() {
			return getRuleContexts(PlotsettingContext.class);
		}
		public PlotsettingContext plotsetting(int i) {
			return getRuleContext(PlotsettingContext.class,i);
		}
		public List<FixedordersContext> fixedorders() {
			return getRuleContexts(FixedordersContext.class);
		}
		public FixedordersContext fixedorders(int i) {
			return getRuleContext(FixedordersContext.class,i);
		}
		public List<CutoffContext> cutoff() {
			return getRuleContexts(CutoffContext.class);
		}
		public CutoffContext cutoff(int i) {
			return getRuleContext(CutoffContext.class,i);
		}
		public List<PrecisionContext> precision() {
			return getRuleContexts(PrecisionContext.class);
		}
		public PrecisionContext precision(int i) {
			return getRuleContext(PrecisionContext.class,i);
		}
		public List<FilenameContext> filename() {
			return getRuleContexts(FilenameContext.class);
		}
		public FilenameContext filename(int i) {
			return getRuleContext(FilenameContext.class,i);
		}
		public List<MaxjumpsContext> maxjumps() {
			return getRuleContexts(MaxjumpsContext.class);
		}
		public MaxjumpsContext maxjumps(int i) {
			return getRuleContext(MaxjumpsContext.class,i);
		}
		public List<PrintContext> print() {
			return getRuleContexts(PrintContext.class);
		}
		public PrintContext print(int i) {
			return getRuleContext(PrintContext.class,i);
		}
		public SettingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_setting; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterSetting(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitSetting(this);
		}
	}

	public final SettingContext setting() throws RecognitionException {
		SettingContext _localctx = new SettingContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_setting);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(188);
			match(T__11);
			setState(189);
			match(T__1);
			setState(203);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__12) | (1L << T__13) | (1L << T__14) | (1L << T__15) | (1L << T__16) | (1L << T__17) | (1L << T__18) | (1L << T__19) | (1L << T__20) | (1L << T__21) | (1L << T__22))) != 0)) {
				{
				setState(201);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case T__12:
					{
					setState(190);
					fixedsteps();
					}
					break;
				case T__13:
					{
					setState(191);
					time();
					}
					break;
				case T__18:
					{
					setState(192);
					remainder();
					}
					break;
				case T__19:
					{
					setState(193);
					identity();
					}
					break;
				case T__14:
					{
					setState(194);
					plotsetting();
					}
					break;
				case T__20:
					{
					setState(195);
					fixedorders();
					}
					break;
				case T__21:
					{
					setState(196);
					cutoff();
					}
					break;
				case T__22:
					{
					setState(197);
					precision();
					}
					break;
				case T__15:
					{
					setState(198);
					filename();
					}
					break;
				case T__16:
					{
					setState(199);
					maxjumps();
					}
					break;
				case T__17:
					{
					setState(200);
					print();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				setState(205);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(206);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FixedstepsContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(HybridAutomatonParser.NUMBER, 0); }
		public FixedstepsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fixedsteps; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterFixedsteps(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitFixedsteps(this);
		}
	}

	public final FixedstepsContext fixedsteps() throws RecognitionException {
		FixedstepsContext _localctx = new FixedstepsContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_fixedsteps);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(208);
			match(T__12);
			setState(209);
			match(NUMBER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TimeContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(HybridAutomatonParser.NUMBER, 0); }
		public TimeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_time; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterTime(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitTime(this);
		}
	}

	public final TimeContext time() throws RecognitionException {
		TimeContext _localctx = new TimeContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_time);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(211);
			match(T__13);
			setState(212);
			match(NUMBER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PlotsettingContext extends ParserRuleContext {
		public List<TerminalNode> VARIABLE() { return getTokens(HybridAutomatonParser.VARIABLE); }
		public TerminalNode VARIABLE(int i) {
			return getToken(HybridAutomatonParser.VARIABLE, i);
		}
		public PlotsettingContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_plotsetting; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterPlotsetting(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitPlotsetting(this);
		}
	}

	public final PlotsettingContext plotsetting() throws RecognitionException {
		PlotsettingContext _localctx = new PlotsettingContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_plotsetting);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(214);
			match(T__14);
			setState(215);
			match(VARIABLE);
			setState(222);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__4) {
				{
				setState(218); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(216);
					match(T__4);
					setState(217);
					match(VARIABLE);
					}
					}
					setState(220); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( _la==T__4 );
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FilenameContext extends ParserRuleContext {
		public TerminalNode VARIABLE() { return getToken(HybridAutomatonParser.VARIABLE, 0); }
		public FilenameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_filename; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterFilename(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitFilename(this);
		}
	}

	public final FilenameContext filename() throws RecognitionException {
		FilenameContext _localctx = new FilenameContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_filename);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(224);
			match(T__15);
			setState(225);
			match(VARIABLE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class MaxjumpsContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(HybridAutomatonParser.NUMBER, 0); }
		public MaxjumpsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_maxjumps; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterMaxjumps(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitMaxjumps(this);
		}
	}

	public final MaxjumpsContext maxjumps() throws RecognitionException {
		MaxjumpsContext _localctx = new MaxjumpsContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_maxjumps);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(227);
			match(T__16);
			setState(228);
			match(NUMBER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PrintContext extends ParserRuleContext {
		public TerminalNode VARIABLE() { return getToken(HybridAutomatonParser.VARIABLE, 0); }
		public PrintContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_print; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterPrint(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitPrint(this);
		}
	}

	public final PrintContext print() throws RecognitionException {
		PrintContext _localctx = new PrintContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_print);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(230);
			match(T__17);
			setState(231);
			match(VARIABLE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class RemainderContext extends ParserRuleContext {
		public TerminalNode EXPONENTIAL() { return getToken(HybridAutomatonParser.EXPONENTIAL, 0); }
		public RemainderContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_remainder; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterRemainder(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitRemainder(this);
		}
	}

	public final RemainderContext remainder() throws RecognitionException {
		RemainderContext _localctx = new RemainderContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_remainder);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(233);
			match(T__18);
			setState(234);
			match(EXPONENTIAL);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IdentityContext extends ParserRuleContext {
		public IdentityContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_identity; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterIdentity(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitIdentity(this);
		}
	}

	public final IdentityContext identity() throws RecognitionException {
		IdentityContext _localctx = new IdentityContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_identity);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(236);
			match(T__19);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FixedordersContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(HybridAutomatonParser.NUMBER, 0); }
		public FixedordersContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fixedorders; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterFixedorders(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitFixedorders(this);
		}
	}

	public final FixedordersContext fixedorders() throws RecognitionException {
		FixedordersContext _localctx = new FixedordersContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_fixedorders);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(238);
			match(T__20);
			setState(239);
			match(NUMBER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CutoffContext extends ParserRuleContext {
		public TerminalNode EXPONENTIAL() { return getToken(HybridAutomatonParser.EXPONENTIAL, 0); }
		public CutoffContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cutoff; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterCutoff(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitCutoff(this);
		}
	}

	public final CutoffContext cutoff() throws RecognitionException {
		CutoffContext _localctx = new CutoffContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_cutoff);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(241);
			match(T__21);
			setState(242);
			match(EXPONENTIAL);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PrecisionContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(HybridAutomatonParser.NUMBER, 0); }
		public PrecisionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_precision; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterPrecision(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitPrecision(this);
		}
	}

	public final PrecisionContext precision() throws RecognitionException {
		PrecisionContext _localctx = new PrecisionContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_precision);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(244);
			match(T__22);
			setState(245);
			match(NUMBER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ModesContext extends ParserRuleContext {
		public List<LocationContext> location() {
			return getRuleContexts(LocationContext.class);
		}
		public LocationContext location(int i) {
			return getRuleContext(LocationContext.class,i);
		}
		public ModesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_modes; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterModes(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitModes(this);
		}
	}

	public final ModesContext modes() throws RecognitionException {
		ModesContext _localctx = new ModesContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_modes);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(247);
			match(T__23);
			setState(248);
			match(T__1);
			setState(252);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VARIABLE) {
				{
				{
				setState(249);
				location();
				}
				}
				setState(254);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(255);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LocationContext extends ParserRuleContext {
		public TerminalNode VARIABLE() { return getToken(HybridAutomatonParser.VARIABLE, 0); }
		public ActivitiesContext activities() {
			return getRuleContext(ActivitiesContext.class,0);
		}
		public InvariantsContext invariants() {
			return getRuleContext(InvariantsContext.class,0);
		}
		public LocationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_location; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterLocation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitLocation(this);
		}
	}

	public final LocationContext location() throws RecognitionException {
		LocationContext _localctx = new LocationContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_location);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(257);
			match(VARIABLE);
			setState(258);
			match(T__1);
			setState(259);
			activities();
			setState(260);
			invariants();
			setState(261);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ActivitiesContext extends ParserRuleContext {
		public List<EquationContext> equation() {
			return getRuleContexts(EquationContext.class);
		}
		public EquationContext equation(int i) {
			return getRuleContext(EquationContext.class,i);
		}
		public ActivitiesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_activities; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterActivities(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitActivities(this);
		}
	}

	public final ActivitiesContext activities() throws RecognitionException {
		ActivitiesContext _localctx = new ActivitiesContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_activities);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(263);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__24) | (1L << T__25) | (1L << T__26) | (1L << T__27))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(264);
			match(T__1);
			setState(268);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VARIABLE) {
				{
				{
				setState(265);
				equation();
				}
				}
				setState(270);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(271);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class InvariantsContext extends ParserRuleContext {
		public ConstrsetContext constrset() {
			return getRuleContext(ConstrsetContext.class,0);
		}
		public InvariantsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_invariants; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterInvariants(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitInvariants(this);
		}
	}

	public final InvariantsContext invariants() throws RecognitionException {
		InvariantsContext _localctx = new InvariantsContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_invariants);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(273);
			match(T__28);
			setState(274);
			match(T__1);
			setState(275);
			constrset();
			setState(276);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class InitContext extends ParserRuleContext {
		public InitstateContext initstate() {
			return getRuleContext(InitstateContext.class,0);
		}
		public InitContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_init; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterInit(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitInit(this);
		}
	}

	public final InitContext init() throws RecognitionException {
		InitContext _localctx = new InitContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_init);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(278);
			match(T__29);
			setState(279);
			match(T__1);
			setState(280);
			initstate();
			setState(281);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class InitstateContext extends ParserRuleContext {
		public TerminalNode VARIABLE() { return getToken(HybridAutomatonParser.VARIABLE, 0); }
		public ConstrsetContext constrset() {
			return getRuleContext(ConstrsetContext.class,0);
		}
		public InitstateContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_initstate; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterInitstate(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitInitstate(this);
		}
	}

	public final InitstateContext initstate() throws RecognitionException {
		InitstateContext _localctx = new InitstateContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_initstate);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(283);
			match(VARIABLE);
			setState(284);
			match(T__1);
			setState(285);
			constrset();
			setState(286);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class UnsafesetContext extends ParserRuleContext {
		public List<BadstateContext> badstate() {
			return getRuleContexts(BadstateContext.class);
		}
		public BadstateContext badstate(int i) {
			return getRuleContext(BadstateContext.class,i);
		}
		public UnsafesetContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unsafeset; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterUnsafeset(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitUnsafeset(this);
		}
	}

	public final UnsafesetContext unsafeset() throws RecognitionException {
		UnsafesetContext _localctx = new UnsafesetContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_unsafeset);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(288);
			match(T__30);
			setState(289);
			match(T__1);
			setState(293);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VARIABLE) {
				{
				{
				setState(290);
				badstate();
				}
				}
				setState(295);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(296);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class BadstateContext extends ParserRuleContext {
		public TerminalNode VARIABLE() { return getToken(HybridAutomatonParser.VARIABLE, 0); }
		public ConstrsetContext constrset() {
			return getRuleContext(ConstrsetContext.class,0);
		}
		public BadstateContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_badstate; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).enterBadstate(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof HybridAutomatonListener ) ((HybridAutomatonListener)listener).exitBadstate(this);
		}
	}

	public final BadstateContext badstate() throws RecognitionException {
		BadstateContext _localctx = new BadstateContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_badstate);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(298);
			match(VARIABLE);
			setState(299);
			match(T__1);
			setState(301);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,20,_ctx) ) {
			case 1:
				{
				setState(300);
				constrset();
				}
				break;
			}
			setState(303);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3/\u0134\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3"+
		"\2\5\2V\n\2\3\3\3\3\3\3\3\3\6\3\\\n\3\r\3\16\3]\5\3`\n\3\3\4\3\4\3\4\7"+
		"\4e\n\4\f\4\16\4h\13\4\3\4\3\4\3\5\3\5\3\5\3\5\3\5\7\5q\n\5\f\5\16\5t"+
		"\13\5\3\6\3\6\3\6\3\6\3\7\3\7\3\b\3\b\3\b\3\b\3\b\3\t\3\t\3\t\3\t\5\t"+
		"\u0085\n\t\3\n\3\n\3\n\7\n\u008a\n\n\f\n\16\n\u008d\13\n\3\n\3\n\3\13"+
		"\3\13\3\13\3\13\3\f\3\f\3\f\7\f\u0098\n\f\f\f\16\f\u009b\13\f\3\r\3\r"+
		"\3\r\3\r\7\r\u00a1\n\r\f\r\16\r\u00a4\13\r\3\16\3\16\3\16\3\16\3\16\3"+
		"\16\3\17\3\17\3\17\3\17\3\20\3\20\3\20\3\20\3\21\3\21\3\21\3\21\3\22\3"+
		"\22\7\22\u00ba\n\22\f\22\16\22\u00bd\13\22\3\23\3\23\3\23\3\23\3\23\3"+
		"\23\3\23\3\23\3\23\3\23\3\23\3\23\3\23\7\23\u00cc\n\23\f\23\16\23\u00cf"+
		"\13\23\3\23\3\23\3\24\3\24\3\24\3\25\3\25\3\25\3\26\3\26\3\26\3\26\6\26"+
		"\u00dd\n\26\r\26\16\26\u00de\5\26\u00e1\n\26\3\27\3\27\3\27\3\30\3\30"+
		"\3\30\3\31\3\31\3\31\3\32\3\32\3\32\3\33\3\33\3\34\3\34\3\34\3\35\3\35"+
		"\3\35\3\36\3\36\3\36\3\37\3\37\3\37\7\37\u00fd\n\37\f\37\16\37\u0100\13"+
		"\37\3\37\3\37\3 \3 \3 \3 \3 \3 \3!\3!\3!\7!\u010d\n!\f!\16!\u0110\13!"+
		"\3!\3!\3\"\3\"\3\"\3\"\3\"\3#\3#\3#\3#\3#\3$\3$\3$\3$\3$\3%\3%\3%\7%\u0126"+
		"\n%\f%\16%\u0129\13%\3%\3%\3&\3&\3&\5&\u0130\n&\3&\3&\3&\2\2\'\2\4\6\b"+
		"\n\f\16\20\22\24\26\30\32\34\36 \"$&(*,.\60\62\64\668:<>@BDFHJ\2\6\3\2"+
		"\"#\3\2,-\3\2()\3\2\33\36\2\u012e\2L\3\2\2\2\4W\3\2\2\2\6a\3\2\2\2\bk"+
		"\3\2\2\2\nu\3\2\2\2\fy\3\2\2\2\16{\3\2\2\2\20\u0080\3\2\2\2\22\u0086\3"+
		"\2\2\2\24\u0090\3\2\2\2\26\u0094\3\2\2\2\30\u009c\3\2\2\2\32\u00a5\3\2"+
		"\2\2\34\u00ab\3\2\2\2\36\u00af\3\2\2\2 \u00b3\3\2\2\2\"\u00bb\3\2\2\2"+
		"$\u00be\3\2\2\2&\u00d2\3\2\2\2(\u00d5\3\2\2\2*\u00d8\3\2\2\2,\u00e2\3"+
		"\2\2\2.\u00e5\3\2\2\2\60\u00e8\3\2\2\2\62\u00eb\3\2\2\2\64\u00ee\3\2\2"+
		"\2\66\u00f0\3\2\2\28\u00f3\3\2\2\2:\u00f6\3\2\2\2<\u00f9\3\2\2\2>\u0103"+
		"\3\2\2\2@\u0109\3\2\2\2B\u0113\3\2\2\2D\u0118\3\2\2\2F\u011d\3\2\2\2H"+
		"\u0122\3\2\2\2J\u012c\3\2\2\2LM\7\3\2\2MN\7\4\2\2NO\5\4\3\2OP\5$\23\2"+
		"PQ\5<\37\2QR\5\6\4\2RS\5D#\2SU\7\5\2\2TV\5H%\2UT\3\2\2\2UV\3\2\2\2V\3"+
		"\3\2\2\2WX\7\6\2\2X_\7-\2\2YZ\7\7\2\2Z\\\7-\2\2[Y\3\2\2\2\\]\3\2\2\2]"+
		"[\3\2\2\2]^\3\2\2\2^`\3\2\2\2_[\3\2\2\2_`\3\2\2\2`\5\3\2\2\2ab\7\b\2\2"+
		"bf\7\4\2\2ce\5\b\5\2dc\3\2\2\2eh\3\2\2\2fd\3\2\2\2fg\3\2\2\2gi\3\2\2\2"+
		"hf\3\2\2\2ij\7\5\2\2j\7\3\2\2\2kr\5\n\6\2lq\5\f\7\2mq\5\16\b\2nq\5\22"+
		"\n\2oq\5\24\13\2pl\3\2\2\2pm\3\2\2\2pn\3\2\2\2po\3\2\2\2qt\3\2\2\2rp\3"+
		"\2\2\2rs\3\2\2\2s\t\3\2\2\2tr\3\2\2\2uv\7-\2\2vw\7$\2\2wx\7-\2\2x\13\3"+
		"\2\2\2yz\7\t\2\2z\r\3\2\2\2{|\7\n\2\2|}\7\4\2\2}~\5\"\22\2~\177\7\5\2"+
		"\2\177\17\3\2\2\2\u0080\u0081\7-\2\2\u0081\u0084\7%\2\2\u0082\u0085\5"+
		"\30\r\2\u0083\u0085\5\32\16\2\u0084\u0082\3\2\2\2\u0084\u0083\3\2\2\2"+
		"\u0085\21\3\2\2\2\u0086\u0087\7\13\2\2\u0087\u008b\7\4\2\2\u0088\u008a"+
		"\5\20\t\2\u0089\u0088\3\2\2\2\u008a\u008d\3\2\2\2\u008b\u0089\3\2\2\2"+
		"\u008b\u008c\3\2\2\2\u008c\u008e\3\2\2\2\u008d\u008b\3\2\2\2\u008e\u008f"+
		"\7\5\2\2\u008f\23\3\2\2\2\u0090\u0091\t\2\2\2\u0091\u0092\7\4\2\2\u0092"+
		"\u0093\7\5\2\2\u0093\25\3\2\2\2\u0094\u0099\t\3\2\2\u0095\u0096\7+\2\2"+
		"\u0096\u0098\t\3\2\2\u0097\u0095\3\2\2\2\u0098\u009b\3\2\2\2\u0099\u0097"+
		"\3\2\2\2\u0099\u009a\3\2\2\2\u009a\27\3\2\2\2\u009b\u0099\3\2\2\2\u009c"+
		"\u00a2\5\26\f\2\u009d\u009e\7*\2\2\u009e\u00a1\5\26\f\2\u009f\u00a1\5"+
		"\26\f\2\u00a0\u009d\3\2\2\2\u00a0\u009f\3\2\2\2\u00a1\u00a4\3\2\2\2\u00a2"+
		"\u00a0\3\2\2\2\u00a2\u00a3\3\2\2\2\u00a3\31\3\2\2\2\u00a4\u00a2\3\2\2"+
		"\2\u00a5\u00a6\7\f\2\2\u00a6\u00a7\7,\2\2\u00a7\u00a8\7\7\2\2\u00a8\u00a9"+
		"\7,\2\2\u00a9\u00aa\7\r\2\2\u00aa\33\3\2\2\2\u00ab\u00ac\7-\2\2\u00ac"+
		"\u00ad\7(\2\2\u00ad\u00ae\5\30\r\2\u00ae\35\3\2\2\2\u00af\u00b0\5\30\r"+
		"\2\u00b0\u00b1\t\4\2\2\u00b1\u00b2\5\30\r\2\u00b2\37\3\2\2\2\u00b3\u00b4"+
		"\7-\2\2\u00b4\u00b5\7&\2\2\u00b5\u00b6\5\32\16\2\u00b6!\3\2\2\2\u00b7"+
		"\u00ba\5\36\20\2\u00b8\u00ba\5 \21\2\u00b9\u00b7\3\2\2\2\u00b9\u00b8\3"+
		"\2\2\2\u00ba\u00bd\3\2\2\2\u00bb\u00b9\3\2\2\2\u00bb\u00bc\3\2\2\2\u00bc"+
		"#\3\2\2\2\u00bd\u00bb\3\2\2\2\u00be\u00bf\7\16\2\2\u00bf\u00cd\7\4\2\2"+
		"\u00c0\u00cc\5&\24\2\u00c1\u00cc\5(\25\2\u00c2\u00cc\5\62\32\2\u00c3\u00cc"+
		"\5\64\33\2\u00c4\u00cc\5*\26\2\u00c5\u00cc\5\66\34\2\u00c6\u00cc\58\35"+
		"\2\u00c7\u00cc\5:\36\2\u00c8\u00cc\5,\27\2\u00c9\u00cc\5.\30\2\u00ca\u00cc"+
		"\5\60\31\2\u00cb\u00c0\3\2\2\2\u00cb\u00c1\3\2\2\2\u00cb\u00c2\3\2\2\2"+
		"\u00cb\u00c3\3\2\2\2\u00cb\u00c4\3\2\2\2\u00cb\u00c5\3\2\2\2\u00cb\u00c6"+
		"\3\2\2\2\u00cb\u00c7\3\2\2\2\u00cb\u00c8\3\2\2\2\u00cb\u00c9\3\2\2\2\u00cb"+
		"\u00ca\3\2\2\2\u00cc\u00cf\3\2\2\2\u00cd\u00cb\3\2\2\2\u00cd\u00ce\3\2"+
		"\2\2\u00ce\u00d0\3\2\2\2\u00cf\u00cd\3\2\2\2\u00d0\u00d1\7\5\2\2\u00d1"+
		"%\3\2\2\2\u00d2\u00d3\7\17\2\2\u00d3\u00d4\7,\2\2\u00d4\'\3\2\2\2\u00d5"+
		"\u00d6\7\20\2\2\u00d6\u00d7\7,\2\2\u00d7)\3\2\2\2\u00d8\u00d9\7\21\2\2"+
		"\u00d9\u00e0\7-\2\2\u00da\u00db\7\7\2\2\u00db\u00dd\7-\2\2\u00dc\u00da"+
		"\3\2\2\2\u00dd\u00de\3\2\2\2\u00de\u00dc\3\2\2\2\u00de\u00df\3\2\2\2\u00df"+
		"\u00e1\3\2\2\2\u00e0\u00dc\3\2\2\2\u00e0\u00e1\3\2\2\2\u00e1+\3\2\2\2"+
		"\u00e2\u00e3\7\22\2\2\u00e3\u00e4\7-\2\2\u00e4-\3\2\2\2\u00e5\u00e6\7"+
		"\23\2\2\u00e6\u00e7\7,\2\2\u00e7/\3\2\2\2\u00e8\u00e9\7\24\2\2\u00e9\u00ea"+
		"\7-\2\2\u00ea\61\3\2\2\2\u00eb\u00ec\7\25\2\2\u00ec\u00ed\7/\2\2\u00ed"+
		"\63\3\2\2\2\u00ee\u00ef\7\26\2\2\u00ef\65\3\2\2\2\u00f0\u00f1\7\27\2\2"+
		"\u00f1\u00f2\7,\2\2\u00f2\67\3\2\2\2\u00f3\u00f4\7\30\2\2\u00f4\u00f5"+
		"\7/\2\2\u00f59\3\2\2\2\u00f6\u00f7\7\31\2\2\u00f7\u00f8\7,\2\2\u00f8;"+
		"\3\2\2\2\u00f9\u00fa\7\32\2\2\u00fa\u00fe\7\4\2\2\u00fb\u00fd\5> \2\u00fc"+
		"\u00fb\3\2\2\2\u00fd\u0100\3\2\2\2\u00fe\u00fc\3\2\2\2\u00fe\u00ff\3\2"+
		"\2\2\u00ff\u0101\3\2\2\2\u0100\u00fe\3\2\2\2\u0101\u0102\7\5\2\2\u0102"+
		"=\3\2\2\2\u0103\u0104\7-\2\2\u0104\u0105\7\4\2\2\u0105\u0106\5@!\2\u0106"+
		"\u0107\5B\"\2\u0107\u0108\7\5\2\2\u0108?\3\2\2\2\u0109\u010a\t\5\2\2\u010a"+
		"\u010e\7\4\2\2\u010b\u010d\5\34\17\2\u010c\u010b\3\2\2\2\u010d\u0110\3"+
		"\2\2\2\u010e\u010c\3\2\2\2\u010e\u010f\3\2\2\2\u010f\u0111\3\2\2\2\u0110"+
		"\u010e\3\2\2\2\u0111\u0112\7\5\2\2\u0112A\3\2\2\2\u0113\u0114\7\37\2\2"+
		"\u0114\u0115\7\4\2\2\u0115\u0116\5\"\22\2\u0116\u0117\7\5\2\2\u0117C\3"+
		"\2\2\2\u0118\u0119\7 \2\2\u0119\u011a\7\4\2\2\u011a\u011b\5F$\2\u011b"+
		"\u011c\7\5\2\2\u011cE\3\2\2\2\u011d\u011e\7-\2\2\u011e\u011f\7\4\2\2\u011f"+
		"\u0120\5\"\22\2\u0120\u0121\7\5\2\2\u0121G\3\2\2\2\u0122\u0123\7!\2\2"+
		"\u0123\u0127\7\4\2\2\u0124\u0126\5J&\2\u0125\u0124\3\2\2\2\u0126\u0129"+
		"\3\2\2\2\u0127\u0125\3\2\2\2\u0127\u0128\3\2\2\2\u0128\u012a\3\2\2\2\u0129"+
		"\u0127\3\2\2\2\u012a\u012b\7\5\2\2\u012bI\3\2\2\2\u012c\u012d\7-\2\2\u012d"+
		"\u012f\7\4\2\2\u012e\u0130\5\"\22\2\u012f\u012e\3\2\2\2\u012f\u0130\3"+
		"\2\2\2\u0130\u0131\3\2\2\2\u0131\u0132\7\5\2\2\u0132K\3\2\2\2\27U]_fp"+
		"r\u0084\u008b\u0099\u00a0\u00a2\u00b9\u00bb\u00cb\u00cd\u00de\u00e0\u00fe"+
		"\u010e\u0127\u012f";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}