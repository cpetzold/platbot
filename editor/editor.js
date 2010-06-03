Editor = function() {

  return {
    
    init: function() {
      var self = Editor;
      
      self.tilesize = 32;
      self.tileset = "grass.png";
      
      self.window = $(window);

      self.el = {};

      self.el.inspector = $('#inspector');
      self.el.newtile = $('#newtile');
      self.el.tileset = $('#tileset');
      self.el.tilesize = $('#tilesize');
      self.el.tilesizeamt = $('#tilesize_amt');
      
      
      self.canvas = $('#canvas')[0];
      self.display = self.canvas.getContext('2d');
      
      self.canvas.width = self.window.width();
      self.canvas.height = self.window.height();;
      
      self.el.inspector.dialog({
        closeOnEscape: false,
        width: 250,
        height: 600,
        position: [15,15],
        buttons: { "Save": self.save, "Reset": self.reset }
      });
      self.el.inspector.tabs();
      
      self.el.newtile.dialog({
        // autoOpen: false,
        modal: true,
        buttons: { "Add": self.addtile, "Cancel": function() { $(this).dialog("close"); } },
        open: self.openNewtile
      });
      
      self.el.tilesize.slider({
        range: "max",
        min: 16,
        max: 128,
        value: 32,
        slide: function(e, ui) {
          self.el.tilesizeamt.text(ui.value+"x"+ui.value);
          self.tilesize = ui.value;
          self.draw();
        }
      });
      self.el.tilesizeamt.text(self.el.tilesize.slider("value")+"x"+self.el.tilesize.slider("value"));
      
      self.el.tileset.children().click(function() {
        $(this).addClass("selected").siblings().removeClass("selected");
      });
      
      self.draw();
    },
    
    save: function() {
      
    },
    
    reset: function() {
      
    },
    
    addtile: function() {
      
      
    },
    
    openNewtile: function(e, ui) {
      var self = Editor;
      
      for (var x = 0; x < self.el.tileset.width(); x+=self.tilesize) {
        for (var y = 0; y < self.el.tileset.height(); y+=self.tilesize) {
          self.el.tileset.append("<li x='"+x/self.tilesize+"' y='"+y/self.tilesize+"'></li>");
        }
      }
    },
    
    draw: function() {
      var self = Editor;
      
      self.display.clearRect(0,0,self.canvas.width,self.canvas.height);
      
      
      self.display.strokeStyle = "#333";
      for (var i = self.tilesize; i < self.canvas.width; i+=self.tilesize) {
        self.display.beginPath();
        self.display.moveTo(i+.5, 0);
        self.display.lineTo(i+.5, self.canvas.height);
        self.display.stroke();
      }
      
      for (var i = self.tilesize; i < self.canvas.height; i+=self.tilesize) {
        self.display.beginPath();
        self.display.moveTo(0, i+.5);
        self.display.lineTo(self.canvas.width, i);
        self.display.stroke();
      }
      
      
    }
    
    
    
    
  };
}();


$(Editor.init);