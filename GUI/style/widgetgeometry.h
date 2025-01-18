#ifndef WIDGETGEOMETRY_H
#define WIDGETGEOMETRY_H
struct WidgetGeometry {
    int width;
    int height;
    int xPos;
    int yPos;

    WidgetGeometry() : width(0), height(0), xPos(0), yPos(0) {}

    WidgetGeometry(int w, int h, int x, int y)
        : width(w), height(h), xPos(x), yPos(y) {}
};
#endif // WIDGETGEOMETRY_H
