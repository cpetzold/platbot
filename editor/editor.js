Editor = function() {

  return {
    
    init: function() {
      var self = Editor;
      
      self.pos = [290, 15];
      self.last = [0, 0];
      self.moving = false;
      self.canvassize = [16,16];
      
      self.tiledefs = [];
      self.tiles = new Array();
      
      self.tilesize = 32;
      self.tileset = new Image();
      self.tileset.src = "tilesets/grass.png";
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
        pencil: $('#pencil'),
        eraser: $('#eraser')
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
          self.draw();
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
          self.draw();
        }
      });
      self.el.canvasheight_amt.text(self.el.canvasheight.slider("value"));
      
      self.el.toolbar.buttonset();
      self.el.pencil.button("option", {
        icons: { primary: "ui-icon-pencil" },
        text: false
      });
      self.el.eraser.button("option", {
        icons: { primary: "ui-icon-battery-0" },
        text: false
      });
      
      self.initTileset();
      
      self.el.tileset.children().click(function() {
        $(this).addClass("selected").siblings().removeClass("selected");
        
        self.offset = [parseInt($(this).attr("x")), parseInt($(this).attr("y"))];
        console.log(self.offset);
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
        self.pos[0] += e.clientX - self.last[0];
        self.pos[1] += e.clientY - self.last[1];
        self.last = [e.clientX, e.clientY];
        self.draw();
      } else if (self.el.pencil.attr("checked")) {
        var loc = self.coords([e.clientX, e.clientY]);
        
        self.draw();
        self.drawTile(loc, self.offset);
      }
    },
    
    mousedown: function(e) {
      var self = Editor;
      
      if (e.button == 0 && e.shiftKey) {
        self.last = [e.clientX, e.clientY];
        self.moving = true;
        e.preventDefault();
      } else if (self.el.pencil.attr("checked")) {
        var loc = self.coords([e.clientX, e.clientY]);
        self.tiles[loc[1]][loc[0]] = self.offset;
        console.log(self.tiles);
      }
    },
    
    mouseup: function(e) {
      var self = Editor;
      if (e.button == 0) {
        self.moving = false;
      }
    },
    
    resize: function() {
      var self = Editor;
      
      self.canvas.width = self.window.width();
      self.canvas.height = self.window.height();
      
      self.tiles.length = self.canvassize[1];
      
      for (var i = 0; i < self.tiles.length; i++) {
        self.tiles[i] = new Array();
        self.tiles[i].length = self.canvassize[0];
      }
      
      self.draw();
    },
    
    save: function() {
      
    },
    
    reset: function() {
      
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
      
      
    }
    
    
    
    
  };
}();


$(Editor.init);