#ifndef README_H
#define README_H

/*
 *
 *  Graphing Calculator
 *
 *  Introduction
 *      This is a graphing calculator written with sfml. The graphs are drawn
 *      using only a rectangle shape and change its position overtime. Backend
 *      classes like rpn and shunting yards are for creating infix and postfix
 *      and do the calculations.Frontend classes like graph and sidebar are
 *      for what is shown on the window. This application is OOP-based with
 *      implemented storation classes like vector and stack.
 *
 *  Utilities
 *      - For any given function of x or solvable equation, this application
 *        provides a graph or/and a specific answer.
 *      - For any graph, this application is able to zoom and shift to all
 *        direction.
 *      - For all user-given attribtes could be saved, such as equations and
 *        setting (includes, angle, domian, x min, etc)
 *      - A multigraph function is provided, which means, multiple graph could
 *        be drawn onto the window. However, the more graphs it have, less
 *        points will be provided for the cpu usage concern.
 *      - Polar graph mode is provided.
 *  Control
 *      Buttons
 *          Save setting
 *              - Save the current setting includes angle, domain, xmin, xmax,
 *              equation, points, window/sidebar size, etc.
 *          Save
 *              - Save the equations from temparory save (left side of the
 *              sidebar)to the history save (right side of the sidebar)
 *          Polar/Normal
 *              - Change to polar mode, so that all of the inputed equations
 *              become polar.
 *          Enable/Disable Multigraph
 *              - Enables multigraph mode, so if the application will graph
 *              all equation that is clicked, to ungraph it, click the equation
 *              again.
 *          Clear History
 *              - Clear all equations from history panel. However, a backup
 *              file, if accidentally clear all saved equation, one can manuelly
 *              recover the lost datas.
 *          <</>>
 *              - Last page and next page of the history panel
 *
 *      Hotkey
 *          z           -   zoom in
 *          x           -   zoom out
 *          c           -   horizontal zoom in
 *          v           -   horizontal zoom out
 *          a           -   clockwise rotation
 *          s           -   counter clockwise rotation
 *          enter       -   enter typing mode, click again to graph
 *          mouse wheel -   zoom in/out
 *
 *  Functions avalible
 *      sin, cos, tan, arcsin, arccos, arctan, sinh, cosh, tanh, log, ln, e, PI
 *
 *  Font used
 *      Quick sand, PlayfairDisplay, Sharefont from Font squirrel
 *      https://www.fontsquirrel.com/fonts/list/popular
 *
 *
 *
 *
 */

#endif // README_H
