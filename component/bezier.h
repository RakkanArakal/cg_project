#ifndef BEZIER_H
#define BEZIER_H

#include <QPoint>
#include <QVector>
typedef struct
{
    double X;
    double Y;
} PointF;


class Bezier
{
public:
    Bezier();
    PointF tmp_points[100];
    QVector<QPoint> bezier_point;

    QVector<QPoint> bezier(QVector<QPoint> point, int point_count);
    PointF bezier_interpolation_func(double t, PointF *points, int point_count);
    void draw_bezier_curves(PointF *points, PointF *out_points, int point_count);
};

#endif // BEZIER_H
