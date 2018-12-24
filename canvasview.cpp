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


#include "canvasview.h"

#include <qwmatrix.h>


void CanvasView::contentsMousePressEvent( QMouseEvent* evt )
{
    QPoint p = inverseWorldMatrix().map( evt->pos() );
    QCanvasItemList list = canvas()->collisions(p);

    // Deselect current group, unless Shift-clicking to
    // add/remove elements.
    if ( !( evt->state() & ShiftButton ) )
	selection = 0;

    for ( QCanvasItemList::Iterator it = list.begin(); it != list.end(); ++it ) {
	if ( *it == selectionbox ) // Ignore the selectionbox
	    continue;
	if ( ! selection ) { // New selection
	    selection = CanvasGroup::groupContaining( *it );
	    if ( ! selection ) {
		selection = new CanvasGroup;
		selection->add( *it );
	    }
	}
	else if ( selection->contains( *it ) ) {
	    // Click on item already in selection
	    if ( evt->state() & ShiftButton ) {
		// Remove it
		moving_start = p;
		bool b = selection->count() == 1;
		selection->remove( *it );
		if ( b ) // all gone
		    selection = 0;
		break;
	    } else // Ignore it
		return;
	} else // Add to existing selection.
	    selection->add( *it );
	moving_start = p;
	break;
    }
    // Update selection box
    delete selectionbox;
    if ( selection ) {
	selectionbox = new QCanvasRectangle( selection->boundingRect(),
					     canvas() );
	selectionbox->setBrush( NoBrush );
	selectionbox->setPen( QPen( red, 0, DashDotDotLine ) );
	selectionbox->setZ( 9999 );
	selectionbox->show();
    } else
	selectionbox = 0;
    canvas()->update();
}


void CanvasView::contentsMouseMoveEvent( QMouseEvent* evt )
{
    if ( selection ) { // Move selection
	QPoint p = inverseWorldMatrix().map( evt->pos() );
	double dx = p.x() - moving_start.x();
	double dy = p.y() - moving_start.y();
	selection->moveBy( dx, dy );
	selectionbox->moveBy( dx, dy );
	moving_start = p;
	canvas()->update();
    }
}


void CanvasView::clear()
{
    ungroup();
    QCanvasItemList list = canvas()->allItems();
    QCanvasItemList::Iterator it = list.begin();
    for (; it != list.end(); ++it) {
	if ( *it )
	    delete *it;
    }
    canvas()->update();
}


void CanvasView::ungroup()
{
    delete selection;
    delete selectionbox;
    selection = 0;
    selectionbox = 0;
    canvas()->update();
}

