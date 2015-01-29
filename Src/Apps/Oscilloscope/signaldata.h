#ifndef _SIGNAL_DATA_H_
#define _SIGNAL_DATA_H_ 1

#include <qrect.h>
#include "plotiddef.h"
#include <qreadwritelock.h>

// Stores plot data
class SignalData
{
public:
    static SignalData &instance(PlotId pid, CurveId cid);
	
    void append( const QPointF &pos );
    void clearStaleValues( double min );

    int size() const;
    QPointF value( int index ) const;

    QRectF boundingRect() const;

    void lock();
    void unlock();

private:
    SignalData();
    SignalData( const SignalData & );
    SignalData &operator=( const SignalData & );
	
    virtual ~SignalData();
	
    class PrivateData;
    PrivateData *pdata;
};

#endif
