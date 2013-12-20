#include "Planning.h"
#include<FuncLibrary\fusionwidgetfunc.h>

void inputLinkersGenerated(void * widgets, QVector<QString> supporttypeclass, QVector<QVector<QString>> supportname)
{
	PLANNINGFUSIONWIDGETS * Planningwidgets=(PLANNINGFUSIONWIDGETS *)widgets;
}

void inputLinkersGeneratedError(void * widgets)
{
	PLANNINGFUSIONWIDGETS * Planningwidgets=(PLANNINGFUSIONWIDGETS *)widgets;
}

void fusionOpen(void * widgets)
{
	PLANNINGFUSIONWIDGETS * Planningwidgets=(PLANNINGFUSIONWIDGETS *)widgets;
}

void fusionOpenError(void * widgets)
{
	PLANNINGFUSIONWIDGETS * Planningwidgets=(PLANNINGFUSIONWIDGETS *)widgets;
}

void dataInput(void * widgets, int typeclassid, int nameid, void * data)
{
	PLANNINGFUSIONWIDGETS * Planningwidgets=(PLANNINGFUSIONWIDGETS *)widgets;
}

void dataInputError(void * widgets)
{
	PLANNINGFUSIONWIDGETS * Planningwidgets=(PLANNINGFUSIONWIDGETS *)widgets;
}

void dataFused(void * widgets, void * data)
{
	PLANNINGFUSIONWIDGETS * Planningwidgets=(PLANNINGFUSIONWIDGETS *)widgets;
}

void dataFusedError(void * widgets)
{
	PLANNINGFUSIONWIDGETS * Planningwidgets=(PLANNINGFUSIONWIDGETS *)widgets;
}

void fusionClose(void * widgets)
{
	PLANNINGFUSIONWIDGETS * Planningwidgets=(PLANNINGFUSIONWIDGETS *)widgets;
}

void fusionCloseError(void * widgets)
{
	PLANNINGFUSIONWIDGETS * Planningwidgets=(PLANNINGFUSIONWIDGETS *)widgets;
}

//==========================================================
//Add other functions below and make sure to add (extern "C" Q_DECL_EXPORT) in front of the function
