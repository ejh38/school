/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * JFlex 1.5                                                               *
 * Copyright (C) 1998-2009  Gerwin Klein <lsf@jflex.de>                    *
 * All rights reserved.                                                    *
 *                                                                         *
 * License: BSD                                                            *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
package jflex.gui;

import java.awt.Component;

/**
 * Constraints for layout elements of GridLayout
 *
 * @author Gerwin Klein
 * @version JFlex 1.5, $Revision: 586 $, $Date: 2010-03-07 19:59:36 +1100 (Sun, 07 Mar 2010) $
 */
public class GridPanelConstraint {

  int x, y, width, height, handle;
  Component component;

  public GridPanelConstraint(int x, int y, int width, int height, 
                             int handle, Component component) {
    this.x         = x;
    this.y         = y;
    this.width     = width;
    this.height    = height;
    this.handle    = handle;
    this.component = component;
  }
}
