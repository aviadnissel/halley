#pragma once
#include "../ui_widget.h"
#include "halley/core/graphics/sprite/sprite.h"

namespace Halley {
	class UIImage : public UIWidget {
	public:
		explicit UIImage(Sprite sprite, Maybe<UISizer> sizer = {}, Vector4f innerBorder = {});
		explicit UIImage(const String& id, Sprite sprite, Maybe<UISizer> sizer = {}, Vector4f innerBorder = {});

		void draw(UIPainter& painter) const override;
		void update(Time t, bool moved) override;

		void setSprite(Sprite sprite);
		Sprite& getSprite();
		const Sprite& getSprite() const;

		void setLayerAdjustment(int adjustment);
		void setWorldClip(Maybe<Rect4f> worldClip);
		void setSelectable(Colour4f normalColour, Colour4f selColour);
		void setSelectable(Sprite normalSprite, Sprite selectedSprite);

	private:
		Sprite sprite;
		Vector2f topLeftBorder;
		Vector2f bottomRightBorder;
		int layerAdjustment = 0;
		bool dirty = true;
		Maybe<Rect4f> worldClip;
	};
}
