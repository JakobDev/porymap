#include "overlay.h"
#include "scripting.h"
#include "log.h"

void OverlayText::render(QPainter *painter) {
    QFont font = painter->font();
    font.setPixelSize(this->fontSize);
    painter->setFont(font);
    painter->setPen(this->color);
    painter->drawText(this->x, this->y, this->text);
}

void OverlayRect::render(QPainter *painter) {
    if (this->filled) {
        painter->fillRect(this->x, this->y, this->width, this->height, this->color);
    } else {
        painter->setPen(this->color);
        painter->drawRect(this->x, this->y, this->width, this->height);
    }
}

void OverlayImage::render(QPainter *painter) {
    painter->drawImage(this->x, this->y, this->image);
}

void Overlay::renderItems(QPainter *painter) {
    if (this->hidden) return;

    for (auto item : this->items)
        item->render(painter);
}

void Overlay::clearItems() {
    for (auto item : this->items) {
        delete item;
    }
    this->items.clear();
}

QList<OverlayItem*> Overlay::getItems() {
    return this->items;
}

void Overlay::setHidden(bool hidden) {
    this->hidden = hidden;
}

void Overlay::addText(QString text, int x, int y, QString color, int fontSize) {
    this->items.append(new OverlayText(text, x, y, QColor(color), fontSize));
}

void Overlay::addRect(int x, int y, int width, int height, QString color, bool filled) {
    this->items.append(new OverlayRect(x, y, width, height, QColor(color), filled));
}

bool Overlay::addImage(int x, int y, QString filepath, int width, int height, unsigned offset, bool xflip, bool yflip, QList<QRgb> palette, bool setTransparency) {
    QImage image = Scripting::getImage(filepath);
    if (image.isNull()) {
        logError(QString("Failed to load image '%1'").arg(filepath));
        return false;
    }

    int fullWidth = image.width();
    int fullHeight = image.height();

    if (width <= 0)
        width = fullWidth;
    if (height <= 0)
        height = fullHeight;

    if ((unsigned)(width * height) + offset > (unsigned)(fullWidth * fullHeight)) {
        logError(QString("%1x%2 image starting at offset %3 exceeds the image size for '%4'")
                 .arg(width)
                 .arg(height)
                 .arg(offset)
                 .arg(filepath));
        return false;
    }

    // Get specified subset of image
    if (width != fullWidth || height != fullHeight)
        image = image.copy(offset % fullWidth, offset / fullWidth, width, height);

    if (xflip || yflip)
        image = image.transformed(QTransform().scale(xflip ? -1 : 1, yflip ? -1 : 1));

    for (int i = 0; i < palette.size(); i++)
        image.setColor(i, palette.at(i));

    if (setTransparency)
        image.setColor(0, qRgba(0, 0, 0, 0));

    this->items.append(new OverlayImage(x, y, image));
    return true;
}

bool Overlay::addImage(int x, int y, QImage image) {
    if (image.isNull()) {
        logError(QString("Failed to load custom image"));
        return false;
    }
    this->items.append(new OverlayImage(x, y, image));
    return true;
}
