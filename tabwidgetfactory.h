#ifndef TABWIDGETFACTORY_H
#define TABWIDGETFACTORY_H
#include "QWidget"
#include "imagelist.h"
#include "timetabdaylistwidget.h"
#include "timetabrandomlistwidget.h"
#include "timetabweeklistwidget.h"

class TabWidgetFactory {
public:
    virtual ~TabWidgetFactory() = default;
    virtual BaseListWidget* createWidget(QWidget* parent) = 0;
};

class RandomTabWidgetFactory : public TabWidgetFactory {
public:
    BaseListWidget* createWidget(QWidget* parent) override {
        auto widget = new TimeTabRandomListWidget(parent);
        return widget;
    }
};

class WeekTabWidgetFactory : public TabWidgetFactory {
public:
    BaseListWidget* createWidget(QWidget* parent) override {
        auto widget = new TimeTabWeekListWidget(parent);
        return widget;
    }
};

class DayTabWidgetFactory : public TabWidgetFactory {
public:
    BaseListWidget* createWidget(QWidget* parent) override {
        auto widget = new TimeTabDayListWidget(parent);
        return widget;
    }
};
#endif // TABWIDGETFACTORY_H
