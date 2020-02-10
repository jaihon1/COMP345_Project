#ifndef Dictionary_hpp
#define Dictionary_hpp

enum class ResourceName {
    Lumber,
    Rock,
    Sheep,
    Wheat
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
