#include "Map.h"

Map::Map() {
  // Default stuff!
}

Map::Map(Gosu::Graphics& graphics, wstring fn) {
  string filename(fn.begin(), fn.end());
  string input;

  ifstream inFile;
  inFile.open(filename.c_str());
  char buf[65536];
  while (inFile.good()) {
    inFile.getline(buf, 65536);
    input += buf;
  }
  inFile.close();

  stringstream stream(input);

  Object root;
  Reader::Read(root, stream);

  String name = root["name"];
  String author = root["author"];
  String url = root["url"];
  String version = root["version"];
  String tilesetFilename = root["tileset"]["image"];
  Number tileSizeNum = root["tileset"]["tilesize"];
  
  this->tilesize = tileSizeNum.Value();
  
  string ts = tilesetFilename.Value();
  this->tileset.assign(ts.begin(), ts.end());
  this->tileset = Gosu::resourcePrefix() + this->tileset;
  
  wcout << this->tileset << endl;
  
  Array tiledefs = root["tiledefs"];
  Array tiles = root["tiles"];

  vector<Tile> tileDefinitions;
  
  Array::const_iterator itTiledefs(tiledefs.Begin()), itTiledefsEnd(tiledefs.End());
  for (; itTiledefs != itTiledefsEnd; ++itTiledefs) {

    Object def = *itTiledefs;

    if (def.Find("offset") == def.End()) {
      Tile tile(graphics, this->tileset, -this->tilesize, -this->tilesize, this->tilesize, false);
      tileDefinitions.push_back(tile);
    } else {
      Number offX = def["offset"][0];
      Number offY = def["offset"][1];
      Boolean solid = def["solid"];      
      Tile tile(graphics, this->tileset, offX.Value(), offY.Value(), this->tilesize, solid.Value());
      tileDefinitions.push_back(tile);
    }
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

      tile.setPosition(Vec(x * this->tilesize, y * this->tilesize));

      tileRow.insert(tileRow.begin()+x, tile);
      x++;
    }

    this->tiles.insert(this->tiles.begin() + y, tileRow);
    x = 0;
    y++;
  }

  this->dim = Vec(this->tiles[0].size(), this->tiles.size());
}


void Map::draw() {
  for (int y = 0; y < this->dim.y; y++) {
    for (int x = 0; x < this->dim.x; x++) {
      

      if (this->tiles[y][x].isVisible()) {
        this->tiles[y][x].draw(x * this->tilesize, y * this->tilesize, 1);
      }

    }
  }
}


