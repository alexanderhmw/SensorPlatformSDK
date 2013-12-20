#ifndef COLLISION_DETECT_H
#define COLLISION_DETECT_H

#include "Planning_def.h"
#include "kelly_PG.h"

Q_DECL_EXPORT bool cordProjection(PLANNINGFUSIONPARAMS * params, POSNODE * posnode, URGSENSORDATA * urgdata, POSNODE & rearpos, QVector<LPPOINT2D> & lppoints);
Q_DECL_EXPORT bool collisionDetection(TRAJEC_SETS & trajectoryset, QVector<LPPOINT2D> & lppoints);

#endif