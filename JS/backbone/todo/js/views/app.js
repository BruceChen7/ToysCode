var app = app || {};

app.AppView = Backbone.View.extend({
    // 获取todoapp对应的元素
    el: ".todoapp",
    statsTemplate: _.template( $('#stats-template').html()),
    
    initialize: function() {
        this.allCheckbox = this.$('.toggle-all')[0];
         
        //获取#todoapp 下对应的子元素input，其ID为new-todo
        this.$input = this.$('#new-todo');
         
        this.$footer = this.$("#footer");
        this.$main = this.$('#main');
        
        
        this.listenTo(app.Todos, 'add', this.addOne);
        this.listenTo(app.Todos, 'reset', this.addAll);
        
        this.listenTo(app.Todos, 'change:completed', this.filterOne);
        this.listenTo(app.Todos, 'filter',this.filterAll );
        this.listenTo(app.Todos, 'all', this.render);
        
        app.Todos.fetch();
    } ,
    
    addOne: function(todo) {
        var view = new app.TodoView({model: todo});
        $('#todo-list').append(view.render.el);
    },
    
    addAll:function() {
        this.$("#todo-list").html('');
        app.Todos.each(this.addOne,this);
    },
    
    // 添加事件
    events: {
      "keypress #new-todo": 'createOnEnter',
      'click #clear-completed': 'clearCompleted',
      'click #toggle-all': 'toggleAllComplete'  
    },
    
    render: function() {
        var completed = app.Todos.completed().length;
        var remaining = app.Todos.remaining().length;
        
        
        if(app.Todos.length) {
            this.$main.show();
            this.$footer.show();
            
            this.$footer.html(this.statsTemplate({
                complete: completed,
                remaining: remaining
            }))
            
            this.$('#filters li a')
            .removeClass('selected')
            .filter('[href="#/]' + (app.TodoFilter || '') + '"]')
        } else {
            
            this.$main.hide();
            this.$footer.hide();
        }
        
        this.allCheckbox.checked = !remaining;
        
    } ,
    
    filterOne: function(todo) {
        todo.trigger('visible');
    },
    
    filterAll: function() {
        app.Todos.each(this.filterOne, this);
    },
    
    newAttributes: function() {
        return {
            title: this.$input.val().trim(),
            order: app.Todos.nextOrder(),
            completed: false
        };
    },
    
    // 用户在input 元素上按回车键的时候，创建一个新的Todo模型，并保存到localStorage中
    // 并且重置input元素
    createOnEnter: function(event) {
        if(event.which !== ENTER_KEY || !this.$input.val().trim()) {
            return ;
        }
        app.Todos.create(this.newAttributes());
        this.$input.val('');
    },
    
    // 用户选中clear-completed的复选框的时候，删除所有已完成的todo选项
    clearCompleted: function() {
        _.invoke(app.Todos.completed(), 'destory');
        return false;
    },
    
    //选中所有复选框
    toggleAllComplete: function() {
        var completed = this.allCheckbox.checked;
        
        app.Todos.each(function(todo) {
            todo.save({
                'completed': completed
            });
        });
    }
});