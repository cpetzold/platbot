Editor = function() {

  return {
    
    init: function() {
      var self = Editor;
      
      self.moving = false;
      self.drawing = false;
      
      self.pos = [290, 15];
      self.last = [0, 0];
      self.canvassize = [16,16];
      
      self.tiledefs = [];
      self.tiles = new Array();
      
      self.tilesize = 32;
      self.tilesetsrc = "grass.png";
      self.tileset = new Image();
      self.tileset.src = "tilesets/"+self.tilesetsrc;
      self.offset = [0, 0];
      
      self.window = $(window);

      self.el = {
        inspector: $('#inspector'),
        newtile: $('#newtile'),
        tileset: $('#tileset'),
        canvaswidth: $('#canvaswidth'),
        canvasheight: $('#canvasheight'),
        canvaswidth_amt: $('#canvaswidth_amt'),
        canvasheight_amt: $('#canvasheight_amt'),
        canvas: $('#canvas'),
        toolbar: $('#toolbar'),
        drawtype: $('#drawtype'),
        brush: $('#brush'),
        pencil: $('#pencil'),
        eraser: $('#eraser'),
        fill: $('#fill'),
        single: $('#single')
      };
      
      self.canvas = self.el.canvas[0];
      self.display = self.canvas.getContext('2d');
      
      self.resize();
      
      self.el.inspector.dialog({
        closeOnEscape: false,
        width: 250,
        height: 600,
        position: [15,15],
        buttons: { "Save": self.save, "Reset": self.reset }
      });
      self.el.inspector.tabs();
      
      self.el.canvaswidth.slider({
        range: "max",
        min: 16,
        max: 2048,
        value: self.canvassize[0],
        change: function(e, ui) {
          self.el.canvaswidth_amt.text(ui.value);
          self.canvassize[0] = ui.value;
          self.resize();
        }
      });
      self.el.canvaswidth_amt.text(self.el.canvaswidth.slider("value"));
      
      self.el.canvasheight.slider({
        range: "max",
        min: 16,
        max: 2048,
        value: self.canvassize[1],
        change: function(e, ui) {
          self.el.canvasheight_amt.text(ui.value);
          self.canvassize[1] = ui.value;
          self.resize();
        }
      });
      self.el.canvasheight_amt.text(self.el.canvasheight.slider("value"));
      
      self.el.drawtype.buttonset();
      self.el.pencil.button("option", {
        icons: { primary: "ui-icon-pencil" },
        text: false
      });
      self.el.eraser.button("option", {
        icons: { primary: "ui-icon-battery-0" },
        text: false
      });
      
      self.el.brush.buttonset();
      
      self.initTileset();
      
      self.el.tileset.children().click(function() {
        $(this).addClass("selected").siblings().removeClass("selected");
        self.offset = [parseInt($(this).attr("x")), parseInt($(this).attr("y"))];
      });
      self.el.tileset.children().first().addClass("selected");
      
      self.el.canvas.mousedown(self.mousedown).mouseup(self.mouseup).mousemove(self.mousemove).mouseleave(self.mouseup);
      
      self.draw();
    },
    
    initTileset: function() {
      var self = Editor;
      
      for (var x = 0; x < 128; x+=self.tilesize) {
        for (var y = 0; y < 128; y+=self.tilesize) {
          self.el.tileset.append("<li x='"+x/self.tilesize+"' y='"+y/self.tilesize+"'></li>");
        }
      }
    },
    
    coords: function(o) {
      var self = Editor;
      var x = Math.floor((o[0] - self.pos[0]) / 32);
      var y = Math.floor((o[1] - self.pos[1]) / 32);
      
      if (x < 0) x = 0;
      else if (x >= self.canvassize[0]) x = self.canvassize[0]-1;
      
      if (y < 0) y = 0;
      else if (y >= self.canvassize[1]) y = self.canvassize[1]-1;

      return [x, y];
    },
    
    drawTile: function(loc, off) {
      var self = Editor;
      var x = self.pos[0] + (loc[0] * self.tilesize);
      var y = self.pos[1] + (loc[1] * self.tilesize);
      self.display.drawImage(self.tileset, off[1]*self.tilesize, off[0]*self.tilesize, self.tilesize, self.tilesize, x, y, self.tilesize, self.tilesize);
    },
    
    mousemove: function(e) {
      var self = Editor;

      if (self.moving) {        
        self.pos[0] += e.pageX - self.last[0];
        self.pos[1] += e.pageY - self.last[1];
        self.last = [e.pageX, e.pageY];
        self.draw();
      } else if (self.el.single.attr("checked") || self.el.fill.attr("checked")) {
        var loc = self.coords([e.pageX, e.pageY]);
        
        self.draw();
        
        if (self.el.pencil.attr("checked")) {
          self.drawTile(loc, self.offset);
        }
        
        if (self.drawing) {
          var offset = self.el.pencil.attr("checked") ? self.offset : undefined;
          self.fillTile(offset, loc);
        }
        
      }
    },
    
    mousedown: function(e) {
      var self = Editor;
      
      if (e.button == 0) {
        var loc = self.coords([e.clientX, e.clientY]);
        if (e.shiftKey) {
          self.last = [e.clientX, e.clientY];
          self.moving = true;
          e.preventDefault();
        } else if (self.el.single.attr("checked")) {
          var offset = self.el.pencil.attr("checked") ? self.offset : undefined;
          self.fillTile(offset, loc);
          self.drawing = true;
        } else if (self.el.fill.attr("checked")) {
          var offset = self.el.pencil.attr("checked") ? self.offset : undefined;
          self.fill(offset, loc);
        }
      }
      
      
    },
    
    mouseup: function(e) {
      var self = Editor;
      if (e.button == 0) {
        self.moving = false;
        self.drawing = false;
      }
      self.draw();
    },
    
    resize: function() {
      var self = Editor;
      
      self.canvas.width = self.window.width();
      self.canvas.height = self.window.height();
      
      self.tiles.length = self.canvassize[1];
      
      for (var i = 0; i < self.tiles.length; i++) {
        if (!self.tiles[i]) self.tiles[i] = new Array();
        self.tiles[i].length = self.canvassize[0];
      }
      
      self.draw();
    },
    
    save: function() {
      var self = Editor;
      
      var map = {
        "name": $("#name").val(),
        "author": $("#author").val(),
        "url": $("#url").val(),
        "version": $("#version").val(),
        "tileset": {
          "image": self.tilesetsrc,
          "tilesize": self.tilesize
        },
        "tiledefs": [],
        "tiles":[]
      };
      
      
      map.tiledefs[0] = { "solid": false };
      
      for (var i = 0; i < self.tiles.length; i++) {
        map.tiles[i] = self.cloneObj(self.tiles[i]);
      }
      
      
      for (var i = 0; i < self.tiles.length; i++) {
        for (var j = 0; j < self.tiles[i].length; j++) {
          var tile = self.tiles[i][j];
          
          if (tile) {
            
            var found = false;
            for (var k = 0; k < map.tiledefs.length; k++) {
              if (map.tiledefs[k].offset && tile == map.tiledefs[k].offset) {
                map.tiles[i][j] = k;
                found = true;
                break;
              }
            }
            
            if (!found) {
              map.tiles[i][j] = map.tiledefs.length;
              map.tiledefs[map.tiledefs.length] = { "offset": tile, "solid": true };
            }
            
            
          } else {
            map.tiles[i][j] = 0;
          }
          
        }
      }
      
      //console.log(JSON.stringify(map));
      window.location = "map.php?t="+JSON.stringify(map)+"&n="+map.name;
      
    },
    
    reset: function() {
      var self = Editor;
      
    },
    
    fillTile: function(o, loc) {
      var self = Editor;
      self.tiles[loc[1]][loc[0]] = o;
    },
    
    fill: function(o, loc) {
      var self = Editor;
      var original = self.tiles[loc[1]][loc[0]];
      
      if (original == o) return;
      
      var s = new Array();
      s.push(loc);
      
      while (s.length > 0) {
        loc = s.pop();
        if (original == self.tiles[loc[1]][loc[0]]) {
          self.fillTile(o, loc);

          if (loc[0]-1 >= 0) s.push([loc[0]-1, loc[1]]);
          if (loc[0]+1 < self.canvassize[0]) s.push([loc[0]+1, loc[1]]);
          if (loc[1]-1 >= 0) s.push([loc[0], loc[1]-1]);
          if (loc[1]+1 < self.canvassize[1]) s.push([loc[0], loc[1]+1]);
        }
      }
    },
    
    draw: function() {
      var self = Editor;
      
      // Clearing the screen
      self.display.clearRect(0,0,self.canvas.width,self.canvas.height);
      
      self.display.strokeStyle = "#333";
      var loc = 0;
      
      // Drawing vertical lines
      for (var i = 0; i <= self.canvassize[0]; i++) {
        loc = i*self.tilesize;
        self.display.beginPath();
        self.display.moveTo(self.pos[0]+loc+.5, self.pos[1]+0);
        self.display.lineTo(self.pos[0]+loc+.5, self.pos[1]+self.canvassize[1]*self.tilesize);
        self.display.stroke();
      }
      
      // Drawing horizontal lines
      for (var i = 0; i <= self.canvassize[1]; i++) {
        loc = i*self.tilesize;
        self.display.beginPath();
        self.display.moveTo(self.pos[0]+0, self.pos[1]+loc+.5);
        self.display.lineTo(self.pos[0]+self.canvassize[0]*self.tilesize, self.pos[1]+loc+.5);
        self.display.stroke();
      }
      
      // Drawing tiles
      for (var i = 0; i < self.tiles.length; i++) {
        for (var j = 0; j < self.tiles[i].length; j++) {
          if (self.tiles[i][j]) {
            self.drawTile([j,i], self.tiles[i][j]);
          }
        }
      }
      
      
    },
    
    cloneObj: function(obj) {
        if (null == obj || "object" != typeof obj) return obj;
        var copy = obj.constructor();
        for (var attr in obj) {
            if (obj.hasOwnProperty(attr)) copy[attr] = obj[attr];
        }
        return copy;
    }
    
    
    
    
    
  };
}();


$(Editor.init);