//
// Created by noartem on 21.04.2022.
//

#include "Align.h"

namespace elementor {
    Align::Align(Element *child) {
        this->setChild(child);
    }

    Align::Align(Alignment alignment) {
        this->setAlignment(alignment);
    }

    Align::Align(AlignmentFraction alignment) {
        this->setAlignment(alignment);
    }

    Align::Align(Alignment alignment, Element *child) {
        this->setAlignment(alignment);
        this->setChild(child);
    }

    Align::Align(AlignmentFraction alignment, Element *child) {
        this->setAlignment(alignment);
        this->setChild(child);
    }

    void Align::setAlignment(AlignmentFraction alignment) {
        this->alignment = alignment;
    }

    AlignmentFraction getAlignmentValue(Alignment alignmentType) {
        switch (alignmentType)
        {
        case Alignment::BottomCenter:
            return {0.5, 1.0};
        case Alignment::BottomLeft:
            return {0.0, 1.0};
        case Alignment::BottomRight:
            return {1.0, 1.0};
        case Alignment::Center:
            return {0.5, 0.5};
        case Alignment::CenterLeft:
            return {0.0, 0.5};
        case Alignment::CenterRight:
            return {1.0, 0.5};
        case Alignment::TopCenter:
            return {0.5, 0.0};
        case Alignment::TopLeft:
            return {0.0, 0.0};
        case Alignment::TopRight:
            return {1.0, 0.0};
        }
    }

    void Align::setAlignment(Alignment alignmentType) {
        this->alignment = getAlignmentValue(alignmentType);
    }

    AlignmentFraction Align::getAlignment() {
        return this->alignment;
    }

    std::shared_ptr <ElementRenderer> Align::render() {
        return std::make_shared<AlignRenderer>(this->context, this->alignment, this->getChild());
    }

    AlignRenderer::AlignRenderer(ApplicationContext *context, AlignmentFraction alignment, Element *child) {
        this->context = context;
        this->alignment = alignment;
        this->child = child;
    }

    std::vector <RenderElement> AlignRenderer::getChildren(RenderSize size) {
        std::vector <RenderElement> children;

        if (this->child) {
            RenderElement child;
            child.element = this->child;
            child.element->context = context;
            child.renderer = this->child->render();
            child.size = child.renderer->getSize({{0, 0}, size});
            child.position = {(int)(this->alignment.x * (size.width - child.size.width)), (int)(this->alignment.y * (size.height - child.size.height))};

            children.push_back(child);
        }

        return children;
    }
}
