#include "bezier.h"

Bezier::Bezier()
{

}


PointF Bezier::bezier_interpolation_func(double t, PointF *points, int point_count)
{
    for (int i = 1; i < point_count; ++i)
    {
        for (int j = 0; j < point_count - i; ++j)
        {
            if (i == 1)
            {
                tmp_points[j].X = (double)(points[j].X * (1 - t) + points[j + 1].X * t);
                tmp_points[j].Y = (double)(points[j].Y * (1 - t) + points[j + 1].Y * t);
                continue;
            }
            tmp_points[j].X = (double)(tmp_points[j].X * (1 - t) + tmp_points[j + 1].X * t);
            tmp_points[j].Y = (double)(tmp_points[j].Y * (1 - t) + tmp_points[j + 1].Y * t);
        }
    }
    return tmp_points[0];
}
void Bezier::draw_bezier_curves(PointF *points, PointF *out_points,int point_count)
{
    float step = 1.0 / 150;
    float t = 0;
    for (int i = 0; i < 150; i++)
    {
        PointF temp_point = bezier_interpolation_func(t, points,point_count);
        t += step;
        out_points[i] = temp_point;
    }
}

QVector<QPoint> Bezier::bezier(QVector<QPoint> point,int point_count)
{
    bezier_point.clear();
    if(point_count < 2)
        return bezier_point;
    QPoint bpoint;
    PointF pointf;
    int x, y;
    PointF *in = (PointF *)malloc(point_count * sizeof(PointF));
    for (int i = 0; i < point_count; i++)
    {
        in[i].X = point[i].x();
        in[i].Y = point[i].y();
    }

    PointF out[150];
    draw_bezier_curves(in, out,point_count);

    for (int j = 0; j < 150; j++)
    {
        bpoint.setX(out[j].X);
        bpoint.setY(out[j].Y);
        bezier_point.push_back(bpoint);
    }
    free(in);

    return bezier_point;
}
