var app = app || {};
//创建一个todo项
app.TodoView =  Backbone.View.extend({
   tagName: 'li',
   //将id为item-template的模板传给_.template方法进行编译并赋值给template
   //template是一个函数
   template: _.template($('#item-template').html()),
   
   events: {
       'click .toggle': 'togglecompleted',
       'dblclick label' : 'edit',
        'click .destory': 'edit',
       'keypress .edit': 'updateOnEnter',
       'blur .eidt': 'close'
   } ,
   
   
   initialize: function() {
      this.listenTo(this.model, 'change', this.render); 
      this.listenTo(this.model, 'destroy', this.remove);
      this.listenTo(this.model, 'visible', this.toggleVisible);
   },
   
   //
   render: function() {
      
      if(this.model.changed.id !== undefined) {
          return ;
      }
      this.$el.html(this.template(this.model.toJSON()));
      this.$el.toggleClass('completed', this.model.get('completed'));
      this.toggleVisible();
      
      this.$input = this.$(".edit");
      return this;  
   },
   
   toggleVisible: function() {
       this.$el.toggleClass('hidden', this.isHidden());
   },
   
   isHidden: function() {
       var isCompleted = this.model.get('completed');
       return (
           (!isCompleted && app.TodoFilter === 'completed') || 
           (isCompleted && app.TodoFilter === 'active')     
       );
   },
   
   
   togglecompleted: function() {
       this.model.toggle();
   },
   
   edit: function() {
       this.$el.addClass('editing');
       this.$input.focus();
   },
   
   close: function() {
       var value = this.$input.val().trim();
       
       if(value) {
           this.model.save({title: value});
       } else {
           this.clear();
       }
       this.$el.removeClass("editing");
   },
   
   updateOnEnter: function(e) {
       if(e.which === ENTER_KEY) {
           this.close();
       }
   },
   
   clear: function() {
       this.model.destroy();
   }
});