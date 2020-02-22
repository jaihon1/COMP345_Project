#ifndef Dictionary_hpp
#define Dictionary_hpp

enum class ResourceName {
    Lumber = 0,
    Rock = 1,
    Sheep = 2,
    Wheat = 3
};

enum class TileStatus {
	InHand,
	InDeck,
	OnBoard
};

enum ResourceLocation {
	topLeft = 0, topRight = 1, bottomLeft = 2, bottomRight = 3
};

#endif /* Dictionary_hpp */