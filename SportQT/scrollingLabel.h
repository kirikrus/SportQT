#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <qpainter.h>

class ScrollingLabel : public QLabel {
    Q_OBJECT
        Q_PROPERTY(int offset READ offset WRITE setOffset)

public:
    explicit ScrollingLabel(QWidget* parent = nullptr)
        : QLabel(parent), m_offset(0) {
        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &ScrollingLabel::updateOffset);
        m_timer->start(30);
    }

    int offset() const {
        return m_offset;
    }

    void setOffset(int offset) {
        m_offset = offset;
        update();
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.setPen(palette().color(QPalette::WindowText));
        const int textWidth = fontMetrics().horizontalAdvance(text());
        if (textWidth <= width()) {
            QLabel::paintEvent(event);
        }
        else {
            int x = -m_offset;
            int y = (height() - fontMetrics().height()) / 2 + fontMetrics().ascent();
            painter.drawText(x, y, text());
        }
    }

private slots:
    void updateOffset() {
        const int textWidth = fontMetrics().horizontalAdvance(text());
        m_offset += 1;
        if (m_offset > textWidth) {
            m_offset = -textWidth;
        }
        update();
    }

private:
    int m_offset;
    QTimer* m_timer;
};
