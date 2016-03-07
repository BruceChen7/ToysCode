var app = app || {};
//数据模型
app.Todo = Backbone.Model.extend({
    defaults: {
        //默认值设置
        title: "",
        completed:false
    },
    
    toggle: function() {
      this.save({
          completed: !this.get("completed")
      });
    }
});