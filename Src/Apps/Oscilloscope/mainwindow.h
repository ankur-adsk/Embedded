/**************************************************************************

Filename    :   MainWindow.h
Content     :   
Created     :   Feb 2015
Authors     :   Ankur Mohan

Copyright   :   Copyright 2015 Ankur Mohan, All Rights reserved.

Use of this software is subject to the terms of the license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
#include <qwidget.h>
#include "PIDTypeMenu.h"

#define PITCH_CTRL_RANGE	45
#define ROLL_CTRL_RANGE		45
#define YAW_CTRL_RANGE		45

class Plot;
class Knob;
class WheelBox;
class QLineEdit;
class QPushButton;
class QCheckBox;
struct EchoCommand;
class MainWindow;
class Joystick;
class QThread;
class PIDTypeMenu;

class ArrowPadDef: public QWidget
{
	Q_OBJECT
public:
	ArrowPadDef(MainWindow* pmainWindow );

	QPushButton *pButtonUp;
	QPushButton *pButtonDown;
	QPushButton *pButtonRight;
	QPushButton *pButtonLeft;
	
	void ConnectSignals();
	void ResetSetPoint();
public Q_SLOTS:
	void ButtonUpClicked();
	void ButtonDownClicked();
	void ButtonLeftClicked();
	void ButtonRightClicked();

public:
	MainWindow* pMainWindow;
	int PitchDisplacement;
	int RollSetPoint;
};

struct CommonPIDControls // Stores PID Widgets that are common to both Rate/Attitude PID controller
{
	CommonPIDControls() {};
	WheelBox	*pPitchKp;
	WheelBox	*pPitchKi;
	WheelBox	*pPitchKd;
	WheelBox	*pYawKp;
	WheelBox	*pYawKi;
	WheelBox	*pYawKd;
};

struct AttitudePIDControls
{
	AttitudePIDControls():ePIDType(AttitudePIDControl){};
	PIDType ePIDType;
	CommonPIDControls* pCommonPIDCtrl;
};

struct RatePIDControls
{
	RatePIDControls():ePIDType(RatePIDControl){};
	PIDType ePIDType;
	CommonPIDControls* pCommonPIDCtrl;
};

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow( QWidget * = NULL );
	~MainWindow();
	typedef struct PIDParamsDef
	{
		float fKp;
		float fKi;
		float fKd;
	};
	
	typedef struct AttitudePIDParams
	{
		PIDParamsDef PitchPIDParams;
		PIDParamsDef RollPIDParams;
		PIDParamsDef YawPIDParams;
	};

	typedef struct RatePIDParams
	{
		PIDParamsDef PitchPIDParams;
		PIDParamsDef RollPIDParams;
		PIDParamsDef YawPIDParams;
	};

    void	start();
    double	amplitude() const;
    double	frequency() const;
    double	signalInterval() const;
	void	ReadPIDParams(AttitudePIDParams&, RatePIDParams&);
	void	ResetSetPoint();
	// To set up the thread that runs the game controller input
	void	SetupCtrlInput();
	// Create different UI windows and manage layouts
	void CreatePlots();
	void CreatePlotControls();
	void CreatePIDControls();
	void CreateAttitudePIDControls();
	void CreateRatePIDControls();
	void CreateCommonPIDControls();
	void SetPIDParams();
	void CreateQuadStatePanel();
	void CreateQuadControlPanel();
	void ManageLayout();

Q_SIGNALS:
    void amplitudeChanged( double );
    void frequencyChanged( double );
    void signalIntervalChanged( double );
	void startCtrlInputThread();

public Q_SLOTS:
    void setAmplitude( double );
	void textChanged(const QString &);
	void speedChanged(double);
	void PitchHoverAngleChanged(double);
	void RollHoverAngleChanged(double);
	void PitchCtrlChanged(double);
	void RollCtrlChanged(double);
	void YawCtrlChanged(double);
	void PitchKpChanged(double);
	void PitchKiChanged(double);
	void PitchKdChanged(double);
	void YawKpChanged(double);
	void YawKiChanged(double);
	void YawKdChanged(double);
	void FRStateChanged( int state);
	void BRStateChanged( int state);
	void FLStateChanged( int state);
	void BLStateChanged( int state);
	void echoCommand(EchoCommand*);
	void motorToggleClicked();
	// Handle game controller axis movement
	void AxisMoved(long, long, long, int);
	void CreateMenuItems();
	void PIDCtrlTypeChanged();
private:

	// Widget pointers. 
    Knob				*pFrequencyKnob;
    Knob				*pAmplitudeKnob;
    WheelBox			*pTimerWheel;
    WheelBox			*pIntervalWheel;
	WheelBox			*pPitchHoverAngleWheel;
	WheelBox			*pRollHoverAngleWheel;
	WheelBox			*pPitchCtrlWheel;
	WheelBox			*pRollCtrlWheel;
	WheelBox			*pYawCtrlWheel;
	AttitudePIDControls	*pAttPIDCtrl;
	RatePIDControls		*pRatePIDCtrl;
	CommonPIDControls	*pCommonPIDCtrl;

	WheelBox			*pSpeedWheel;
	QPushButton			*pMotorToggle;
	QLineEdit			*pPIDType;
	QLineEdit			*pQuadSpeed;
	QLineEdit			*pQuadPower;
	QLineEdit			*pQuadPKi; // Quad Pitch PID coefficients
	QLineEdit			*pQuadPKp;
	QLineEdit			*pQuadPKd;
	QLineEdit			*pQuadRKi; // Quad Roll PID coefficients
	QLineEdit			*pQuadRKp;
	QLineEdit			*pQuadRKd;
	QLineEdit			*pQuadYKi; // Quad Yaw PID coefficients
	QLineEdit			*pQuadYKp;
	QLineEdit			*pQuadYKd;

	QCheckBox	*pFR, *pFL, *pBR, *pBL;

	// PID Type Menu
	PIDTypeMenu			*pPIDTypeMenu;

	ArrowPadDef* pArrowPad;
	// Widget state variables
	bool		bMotorToggle;
    Plot		*y_plot;
	Plot		*p_plot;
	Plot		*r_plot;

	// Joystick pointer
	Joystick	*pJoystick;
	// Pointer to the thread that runs the joystick
	QThread		*pThread;
	
	double		pamplitude;
	
public:
	// These are the set points we revert to when we reset the motors.
	int					PitchHoverAttitude;
	int					RollHoverAttitude;
	AttitudePIDParams	mAttPIDParams;
	RatePIDParams		mRatePIDParams;
	// These pointers are reset when the PID type is changed
	PIDParamsDef		*pPitchPIDParams, *pYawPIDParams;
	PIDType				ePIDType; // Rate or Attitude


};
