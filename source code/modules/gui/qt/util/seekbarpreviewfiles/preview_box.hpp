#ifndef PREVIEW_BOX_HPP
#define PREVIEW_BOX_HPP

#include <QWidget>
#include <QPoint>

class intf_thread_t;

class PreviewBox : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewBox(QWidget *parent = nullptr, intf_thread_t *p_intf = nullptr);
    void setPosition(const QPoint &target, int tooltipTop, const QRect &windowRect = QRect());
    
protected:
    void paintEvent(QPaintEvent *event) override;
    
private:
    intf_thread_t *p_intf;
    QPoint mTarget;
    int mTooltipTop;
};

#endif // PREVIEW_BOX_HPP