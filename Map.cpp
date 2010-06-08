#include "Map.h"

Map::Map() {
  // Default stuff!
}

Map::Map(string filename, Resources &data) {
  using namespace json;

    cout << "." << endl;
    
  filename = "data/maps/" + filename;

  string input;

  ifstream inFile;
  inFile.open(filename.c_str());
  char buf[2048];
  while (inFile.good()) {
    inFile.getline(buf, 2048);
    input += buf;
  }
  inFile.close();
    
    cout << "." << endl;

  stringstream stream(input);

    cout << "." << endl;

  Object root;
  Reader::Read(root, stream);

    cout << "." << endl;
    
  String name = root["name"];
  String author = root["author"];
  String url = root["url"];
  String version = root["version"];
  String tilesetFilename = root["tileset"]["image"];
  Number tileSizeNum = root["tileset"]["tilesize"];
  int tileSize = tileSizeNum.Value();
    
    cout << "." << endl;

  this->tilesize = tileSize;
  this->tileset = data.GetImage("tilesets/" + tilesetFilename.Value());

  Array tiledefs = root["tiledefs"];
  Array tiles = root["tiles"];

  vector<Tile> tileDefinitions;

    cout << "." << endl;
    
  Array::const_iterator itTiledefs(tiledefs.Begin()), itTiledefsEnd(tiledefs.End());
  for (; itTiledefs != itTiledefsEnd; ++itTiledefs) {
    
    Object def = *itTiledefs;

    if (def.Find("offset") == def.End()) {
      tileDefinitions.push_back(Tile());
      continue;
    }
    
    Number offX = def["offset"][0];
    Number offY = def["offset"][1];
    Boolean solid = def["solid"];
    
    Tile tile(*(this->tileset), solid.Value());

    int left = tileSize * offX.Value();
    int top = tileSize * offY.Value();
    int right = left + tileSize;
    int bottom = top + tileSize;

    tile.SetSubRect(sf::IntRect(left, top, right, bottom));

    tileDefinitions.push_back(tile);
  }


  int x = 0;
  int y = 0;

  Array::const_iterator itTiles(tiles.Begin()), itTilesEnd(tiles.End());
  for (; itTiles != itTilesEnd; ++itTiles) {
    Array row = *itTiles;
    Array::const_iterator itRow(row.Begin()), itRowEnd(row.End());

    vector<Tile> tileRow;

    for (; itRow != itRowEnd; ++itRow) {
      Number tileRef = *itRow;

      Tile tile(tileDefinitions[tileRef.Value()]);

      tile.SetPosition(sf::Vector2f(x*tileSize, y*tileSize));


      tileRow.insert(tileRow.begin()+x, tile);
      x++;
    }

    this->tiles.insert(this->tiles.begin()+y, tileRow);
    x = 0;
    y++;
  }


  this->dim = Vector2D(this->tiles[0].size(), this->tiles.size());
}


void Map::Draw(sf::RenderWindow &window) {

  for (int y = 0; y < this->dim.y; y++) {
    for (int x = 0; x < this->dim.x; x++) {
      
      if (this->tiles[y][x].IsVisible())
        window.Draw(this->tiles[y][x]);

    }
  }

}


Map::~Map() {
  // clean up yo!
}
