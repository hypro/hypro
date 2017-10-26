// Generated from HybridAutomaton.g4 by ANTLR 4.7
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link HybridAutomatonParser}.
 */
public interface HybridAutomatonListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#start}.
	 * @param ctx the parse tree
	 */
	void enterStart(HybridAutomatonParser.StartContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#start}.
	 * @param ctx the parse tree
	 */
	void exitStart(HybridAutomatonParser.StartContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#vardeclaration}.
	 * @param ctx the parse tree
	 */
	void enterVardeclaration(HybridAutomatonParser.VardeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#vardeclaration}.
	 * @param ctx the parse tree
	 */
	void exitVardeclaration(HybridAutomatonParser.VardeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#jumps}.
	 * @param ctx the parse tree
	 */
	void enterJumps(HybridAutomatonParser.JumpsContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#jumps}.
	 * @param ctx the parse tree
	 */
	void exitJumps(HybridAutomatonParser.JumpsContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#transition}.
	 * @param ctx the parse tree
	 */
	void enterTransition(HybridAutomatonParser.TransitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#transition}.
	 * @param ctx the parse tree
	 */
	void exitTransition(HybridAutomatonParser.TransitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#fromto}.
	 * @param ctx the parse tree
	 */
	void enterFromto(HybridAutomatonParser.FromtoContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#fromto}.
	 * @param ctx the parse tree
	 */
	void exitFromto(HybridAutomatonParser.FromtoContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#urgent}.
	 * @param ctx the parse tree
	 */
	void enterUrgent(HybridAutomatonParser.UrgentContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#urgent}.
	 * @param ctx the parse tree
	 */
	void exitUrgent(HybridAutomatonParser.UrgentContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#guard}.
	 * @param ctx the parse tree
	 */
	void enterGuard(HybridAutomatonParser.GuardContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#guard}.
	 * @param ctx the parse tree
	 */
	void exitGuard(HybridAutomatonParser.GuardContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#allocation}.
	 * @param ctx the parse tree
	 */
	void enterAllocation(HybridAutomatonParser.AllocationContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#allocation}.
	 * @param ctx the parse tree
	 */
	void exitAllocation(HybridAutomatonParser.AllocationContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#resetfct}.
	 * @param ctx the parse tree
	 */
	void enterResetfct(HybridAutomatonParser.ResetfctContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#resetfct}.
	 * @param ctx the parse tree
	 */
	void exitResetfct(HybridAutomatonParser.ResetfctContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#aggregation}.
	 * @param ctx the parse tree
	 */
	void enterAggregation(HybridAutomatonParser.AggregationContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#aggregation}.
	 * @param ctx the parse tree
	 */
	void exitAggregation(HybridAutomatonParser.AggregationContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#term}.
	 * @param ctx the parse tree
	 */
	void enterTerm(HybridAutomatonParser.TermContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#term}.
	 * @param ctx the parse tree
	 */
	void exitTerm(HybridAutomatonParser.TermContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#polynom}.
	 * @param ctx the parse tree
	 */
	void enterPolynom(HybridAutomatonParser.PolynomContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#polynom}.
	 * @param ctx the parse tree
	 */
	void exitPolynom(HybridAutomatonParser.PolynomContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#interval}.
	 * @param ctx the parse tree
	 */
	void enterInterval(HybridAutomatonParser.IntervalContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#interval}.
	 * @param ctx the parse tree
	 */
	void exitInterval(HybridAutomatonParser.IntervalContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#equation}.
	 * @param ctx the parse tree
	 */
	void enterEquation(HybridAutomatonParser.EquationContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#equation}.
	 * @param ctx the parse tree
	 */
	void exitEquation(HybridAutomatonParser.EquationContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#constraint}.
	 * @param ctx the parse tree
	 */
	void enterConstraint(HybridAutomatonParser.ConstraintContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#constraint}.
	 * @param ctx the parse tree
	 */
	void exitConstraint(HybridAutomatonParser.ConstraintContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#intervalexpr}.
	 * @param ctx the parse tree
	 */
	void enterIntervalexpr(HybridAutomatonParser.IntervalexprContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#intervalexpr}.
	 * @param ctx the parse tree
	 */
	void exitIntervalexpr(HybridAutomatonParser.IntervalexprContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#constrset}.
	 * @param ctx the parse tree
	 */
	void enterConstrset(HybridAutomatonParser.ConstrsetContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#constrset}.
	 * @param ctx the parse tree
	 */
	void exitConstrset(HybridAutomatonParser.ConstrsetContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#setting}.
	 * @param ctx the parse tree
	 */
	void enterSetting(HybridAutomatonParser.SettingContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#setting}.
	 * @param ctx the parse tree
	 */
	void exitSetting(HybridAutomatonParser.SettingContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#fixedsteps}.
	 * @param ctx the parse tree
	 */
	void enterFixedsteps(HybridAutomatonParser.FixedstepsContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#fixedsteps}.
	 * @param ctx the parse tree
	 */
	void exitFixedsteps(HybridAutomatonParser.FixedstepsContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#time}.
	 * @param ctx the parse tree
	 */
	void enterTime(HybridAutomatonParser.TimeContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#time}.
	 * @param ctx the parse tree
	 */
	void exitTime(HybridAutomatonParser.TimeContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#plotsetting}.
	 * @param ctx the parse tree
	 */
	void enterPlotsetting(HybridAutomatonParser.PlotsettingContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#plotsetting}.
	 * @param ctx the parse tree
	 */
	void exitPlotsetting(HybridAutomatonParser.PlotsettingContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#filename}.
	 * @param ctx the parse tree
	 */
	void enterFilename(HybridAutomatonParser.FilenameContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#filename}.
	 * @param ctx the parse tree
	 */
	void exitFilename(HybridAutomatonParser.FilenameContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#maxjumps}.
	 * @param ctx the parse tree
	 */
	void enterMaxjumps(HybridAutomatonParser.MaxjumpsContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#maxjumps}.
	 * @param ctx the parse tree
	 */
	void exitMaxjumps(HybridAutomatonParser.MaxjumpsContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#print}.
	 * @param ctx the parse tree
	 */
	void enterPrint(HybridAutomatonParser.PrintContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#print}.
	 * @param ctx the parse tree
	 */
	void exitPrint(HybridAutomatonParser.PrintContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#remainder}.
	 * @param ctx the parse tree
	 */
	void enterRemainder(HybridAutomatonParser.RemainderContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#remainder}.
	 * @param ctx the parse tree
	 */
	void exitRemainder(HybridAutomatonParser.RemainderContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#identity}.
	 * @param ctx the parse tree
	 */
	void enterIdentity(HybridAutomatonParser.IdentityContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#identity}.
	 * @param ctx the parse tree
	 */
	void exitIdentity(HybridAutomatonParser.IdentityContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#fixedorders}.
	 * @param ctx the parse tree
	 */
	void enterFixedorders(HybridAutomatonParser.FixedordersContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#fixedorders}.
	 * @param ctx the parse tree
	 */
	void exitFixedorders(HybridAutomatonParser.FixedordersContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#cutoff}.
	 * @param ctx the parse tree
	 */
	void enterCutoff(HybridAutomatonParser.CutoffContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#cutoff}.
	 * @param ctx the parse tree
	 */
	void exitCutoff(HybridAutomatonParser.CutoffContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#precision}.
	 * @param ctx the parse tree
	 */
	void enterPrecision(HybridAutomatonParser.PrecisionContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#precision}.
	 * @param ctx the parse tree
	 */
	void exitPrecision(HybridAutomatonParser.PrecisionContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#modes}.
	 * @param ctx the parse tree
	 */
	void enterModes(HybridAutomatonParser.ModesContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#modes}.
	 * @param ctx the parse tree
	 */
	void exitModes(HybridAutomatonParser.ModesContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#location}.
	 * @param ctx the parse tree
	 */
	void enterLocation(HybridAutomatonParser.LocationContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#location}.
	 * @param ctx the parse tree
	 */
	void exitLocation(HybridAutomatonParser.LocationContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#activities}.
	 * @param ctx the parse tree
	 */
	void enterActivities(HybridAutomatonParser.ActivitiesContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#activities}.
	 * @param ctx the parse tree
	 */
	void exitActivities(HybridAutomatonParser.ActivitiesContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#invariants}.
	 * @param ctx the parse tree
	 */
	void enterInvariants(HybridAutomatonParser.InvariantsContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#invariants}.
	 * @param ctx the parse tree
	 */
	void exitInvariants(HybridAutomatonParser.InvariantsContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#init}.
	 * @param ctx the parse tree
	 */
	void enterInit(HybridAutomatonParser.InitContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#init}.
	 * @param ctx the parse tree
	 */
	void exitInit(HybridAutomatonParser.InitContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#initstate}.
	 * @param ctx the parse tree
	 */
	void enterInitstate(HybridAutomatonParser.InitstateContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#initstate}.
	 * @param ctx the parse tree
	 */
	void exitInitstate(HybridAutomatonParser.InitstateContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#unsafeset}.
	 * @param ctx the parse tree
	 */
	void enterUnsafeset(HybridAutomatonParser.UnsafesetContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#unsafeset}.
	 * @param ctx the parse tree
	 */
	void exitUnsafeset(HybridAutomatonParser.UnsafesetContext ctx);
	/**
	 * Enter a parse tree produced by {@link HybridAutomatonParser#badstate}.
	 * @param ctx the parse tree
	 */
	void enterBadstate(HybridAutomatonParser.BadstateContext ctx);
	/**
	 * Exit a parse tree produced by {@link HybridAutomatonParser#badstate}.
	 * @param ctx the parse tree
	 */
	void exitBadstate(HybridAutomatonParser.BadstateContext ctx);
}