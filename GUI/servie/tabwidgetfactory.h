#ifndef TABWIDGETFACTORY_H
#define TABWIDGETFACTORY_H
#include "QWidget"
#include "imagelist.h"
#include "daylistwidget.h"
#include "randomlistwidget.h"
#include "weeklistwidget.h"

class TabWidgetFactory {
public:
    virtual ~TabWidgetFactory() = default;
    virtual TimeTabChildrenWidget* createWidget(QWidget* parent) = 0;
};

class RandomTabWidgetFactory : public TabWidgetFactory {
public:
    TimeTabChildrenWidget* createWidget(QWidget* parent) override {
        auto widget = new RandomListWidget(parent);
        return widget;
    }
};

class WeekTabWidgetFactory : public TabWidgetFactory {
public:
    TimeTabChildrenWidget* createWidget(QWidget* parent) override {
        auto widget = new WeekListWidget(parent);
        return widget;
    }
};

class DayTabWidgetFactory : public TabWidgetFactory {
public:
    TimeTabChildrenWidget* createWidget(QWidget* parent) override {
        auto widget = new DayListWidget(parent);
        return widget;
    }
};
#endif // TABWIDGETFACTORY_H
