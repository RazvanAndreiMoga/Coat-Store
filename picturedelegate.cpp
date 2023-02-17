#include <QEventLoop>
#include "picturedelegate.h"

PictureDelegate::PictureDelegate(QWidget *parent): QStyledItemDelegate{parent} {

}

void PictureDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QString dog = index.model()->data(index, Qt::EditRole).toString();
    if (index.column() != 5) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    if (dog.contains("https://www.unsplash.com/photos/7s5WyvsMtNc")) {
        QPixmap pixmap("C:/Users/razva/Desktop/t2oop/QtWidgetsApplication1/1.jpg");
        painter->drawPixmap(option.rect, pixmap);
    } else if (dog.contains("https://www.unsplash.com/photos/fYXGEXyaXyM")) {
        QPixmap pixmap("C:/Users/razva/Desktop/t2oop/QtWidgetsApplication1/2.jpg");
        painter->drawPixmap(option.rect, pixmap);
    } else if (dog.contains("https://www.unsplash.com/photos/9ix0Rvy2m5g")) {
        QPixmap pixmap("C:/Users/razva/Desktop/t2oop/QtWidgetsApplication1/3.jpg");
        painter->drawPixmap(option.rect, pixmap);
    } else if (dog.contains("https://www.unsplash.com/photos/FJst_OBiFhY")) {
        QPixmap pixmap("C:/Users/razva/Desktop/t2oop/QtWidgetsApplication1/4.jpeg");
        painter->drawPixmap(option.rect, pixmap);
    }
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() == 1)
        return {32, 64};
    return QStyledItemDelegate::sizeHint(option, index);
}
