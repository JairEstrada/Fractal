/*
    Copyright (C) 1992-2003 Trolltech AS. All Rights Reserved.

    This file ("Example Code"), is part of an example program for Qt,
    and is licensed under the Qt Commercial License Agreement,
    Agreement version 2.4 and higher as well as under the GPL.

    The Example Code is licensed to you "as is" without warranty of
    any kind. To the maximum extent permitted by applicable law,
    Trolltech on behalf of itself and its suppliers, disclaims all
    warranties express or implied, including, but not limited to,
    implied warranties of merchantability and fitness for a particular
    purpose with regard to the Example Code. Trolltech does not
    warrant that the Example Code will satisfy your requirements or
    that it is without defect or error or that the operation thereof
    will be uninterrupted. All use of and reliance on the Example Code
    is at the sole risk of and responsibility of you and your
    customers.

    If you are a holder of a Qt Commercial License Agreement, you can
    use the code under that agreement or you can use it under GPL. If
    you are not a holder of a Qt Commercial License Agreement, you can
    use the code under the GPL. Regardless of the applicable license
    agreement, the Example Code may be used, distributed and modified
    without limitation.
*/


#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include "canvasgroup.h"

#include <qcanvas.h>

class CanvasGroup;
class QPoint;


class CanvasView : public QCanvasView
{
    Q_OBJECT
public:
    CanvasView( QCanvas *canvas, QWidget *parent = 0, const char *name = 0,
		WFlags f = 0 ) : QCanvasView( canvas, parent, name, f ),
				 selection( 0 ), selectionbox( 0 ) {}
    ~CanvasView() {}

    void clear();
    void ungroup();
    void contentsMousePressEvent( QMouseEvent* evt );
    void contentsMouseMoveEvent( QMouseEvent* evt );

private:
    CanvasGroup *selection;
    QCanvasRectangle *selectionbox;
    QPoint moving_start;
};

#endif // CANVASVIEW_H

