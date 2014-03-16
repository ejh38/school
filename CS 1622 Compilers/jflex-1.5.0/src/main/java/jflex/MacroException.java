/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * JFlex 1.5                                                               *
 * Copyright (C) 1998-2009  Gerwin Klein <lsf@jflex.de>                    *
 * All rights reserved.                                                    *
 *                                                                         *
 * License: BSD                                                            *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

package jflex;


/**
 * This Exception is used in the macro expander to report cycles or
 * undefined macro usages.
 *
 * @author Gerwin Klein
 * @version JFlex 1.5, $Revision: 586 $, $Date: 2010-03-07 19:59:36 +1100 (Sun, 07 Mar 2010) $
 */
public class MacroException extends RuntimeException {

  /**
	 * 
	 */
	private static final long serialVersionUID = 275266242549067641L;


  /**
   * Creates a new MacroException without message
   */
  public MacroException() {
  }


  /**
   * Creates a new MacroException with the specified message
   *
   * @param message   the error description presented to the user.
   */
  public MacroException(String message) {
    super(message);
  }

}
