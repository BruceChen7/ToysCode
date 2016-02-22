var notice  = function() {
	//Setting 
	//General 
	var shadow = true;
	var font_size_small = "18px";
	var font_size_big = "24px";
	var font_change_screen_width = 600;
	var animation_delay = 0.3;
	var background_click_dismiss = true;
	 
	 
	var alert_color_success_background = '#57BF57';
	var alert_color_warning_background = '#E3B771';
	var alert_color_error_background = '#E1715B';
	var alert_color_info_background = '#4D82D6';
	var alert_color_text = '#FFF';
	
	var confirm_and_input_color_background = '#4D82D6';
    var confirm_and_input_color_yes_background = '#57BF57';
    var confirm_and_input_color_no_background = '#E17158';
    var confirm_and_input_color_text = '#FFF';
    var confirm_and_input_color_yes_text = '#FFF';
    var confirm_and_input_color_no_text = '#FFF';
	 
	var alert_outer_id = 'notice-alert-outer';
	var alert_inner_id = 'notice-alert-inner';
	var alert_text_id = 'notice-alert_text';
	
	var confirm_outer_id = 'notice-confirm-outer';
    var confirm_inner_id = 'notice-confirm-inner';
    var confirm_background_id = 'notice-confirm-background';
	var confirm_yes_id = 'notice-confirm-yes';
	var confirm_no_id = 'notice-confirm-no';
	var confirm_text_id = 'notice-confirm-text';
	var confirm_yes_text_id = 'notice-confirm-yes';
    var confirm_no_text_id = 'notice-confirm-no';
    
    var input_outer_id = 'notice-inputer-outer';
    var input_inner_id = 'notice-input-inner';
    var input_background_id = 'notice-input-background';
    
    //改变所在元素的字体样式
	var resizeListener = function resizeListener(ele) {
        //如果浏览器的宽度比较小，设置比较小的字体大小。
		if(window.innerWidth <= font_change_screen_width) {
			ele.style.fontSize = font_size_small;
		} else {
			ele.style.fontSize = font_size_big;
		}
	};
	
	var debounce_time = 500;
	var debounce = function debounce(func,wait,immediate) {
		var timeout;
		return function() {
			var context = this;
			var args = arguments;
			var later = function() {
				timeout = null;
				if(!immediate) {
					func.apply(context,args);
				}
			};
            var callNow = immediate && !timeout;
            clearTimeout(timeout);
            timeout = setTimeout(later,wait);
            
            if(callNow) {
                func.apply(context,args);
            }
		}
	}
	
    //监听回车按键和esc键
	window.addEventListener('keydown',function(event) {
		var enter_clicked = (event.which == 13 || event.keyCode == 13);
		var escape_clicked = (event.which == 27 || event.keyCode == 27);
		//如果告警信息已经显示，按回车键，将消失。
        //如果确认消息已经显示，回车键
		if(alert_is_showing) {
			if(enter_clicked || escape_clicked) {
				clearTimeout(alert_timeout_1);
				clearTimeout(alert_timeout_2);
				alert_hide();
			}	
		} else if(confirm_is_showing) {
			if(enter_clicked) {
				confirm_yes.click();
			} else if(escape_clicked) {
				confirm_no.click();
			}
			
		} else if(input_is_showing) {
			if(enter_clicked) {
				input_yes.click();
			} else if(escape_clicked) {
				input_no.click();
			}
		}
	});
	
	if(typeof Element.prototype.addEventListener === 'undefined') {
		Element.prototype.addEventListener = Window.prototype.addEventListener = function(e,callback) {
			e = 'on' + e;
			return this.attachEvent(e,callback);	
		};
	}
	
	var origin_body_heght;
	var origin_body_overflow;
	
	function scroll_disable() {
		origin_body_heght = document.body.style.height;
		origin_body_overflow = document.body.style.overflow;
		document.body.style.height = '100%';
		document.body.style.overflow = 'hidden';
	}
	
	function scroll_enable() {
		document.body.style.height = origin_body_heght;
		document.body.style.overflow = origin_body_overflow;
	}
	
	var alert_outer = document.createElement('div');
	alert_outer.id = alert_outer_id;
	alert_outer.style.position = 'fixed';
	alert_outer.style.top = '0';
	alert_outer.style.left = '0';
	alert_outer.style.zIndex = '999999999';
	alert_outer.style.height = 'auto';
	alert_outer.style.width = '100%';
	
	alert_outer.onclick = function() {
		clearTimeout(alert_timeout_1);
		clearTimeout(alert_timeout_2);
		alert_hide();
	}
	
	
	var alert_text = document.createElement('span');
	alert_text.id = alert_text_id;
	alert_text.style.color = alert_color_text;
	
	if(window.innerWidth <= font_change_screen_width) {
		alert_text.style.fontSize = font_size_small;
		
	} else {
		alert_text.style.fontSize = font_size_big;
	}
	
	var height = 0;
	var alert_is_showing = false;
	var alert_timeout_2;
	var alert_timeout_1;
	var was_clicked_counter = 0;
	
	
	function alert(type,message, seconds) {
		document.activeElement.blur();
		was_clicked_counter++;
		setTimeout(function() {
			was_clicked_counter--;
		},(animation_delay * 1000 + 10));
		
		if(was_clicked_counter == 1) {
			if (alert_is_showing) {
				clearTimeout(alert_timeout_1);
				clearTimeout(alert_timeout_2);
				alert_hide(function() {
					alert_show(type,message,seconds);
				});
			} else {
				alert_show(type,message,seconds);
			}
		}
	}
	
	function alert_show(type,message,seconds) {
		alert_is_showing = true;
		var duration =  0;
		
		if (typeof seconds == 'undefined') {
			duration = 3000;
		} else if (seconds < 1) {
			duration = 1000;
		} else {
			duration =  seconds * 1000;
		}
		
		switch(type) {
			case 1:
				alert_outer.style.backgroundColor = alert_color_success_background;
				break;
			case 2:
				alert_outer.style.backgroundColor = alert_color_warning_background;
				break;
			case 3:
				alert_outer.style.backgroundColor = alert_color_error_background;
				break;
			case 4:
				alert_outer.style.backgroundColor = alert_color_info_background;
				break;
				
		}
		alert_text.innerHTML = message;
		alert_outer.style.top = '-10000px';
		alert_outer.style.display = 'table'; 
		alert_outer.style.top = '-' + alert_outer.offSetHeigt - 5 + 'px';
		alert_time_out1 = setTimeout(function() {
			if(shadow) {
				alert_outer.style.boxShadow = '0px 0px 10px 0px rgba(0,0,0,0.5)';
			}
			alert_outer.style.MozTransition = 'all' + animation_delay + 's ease';
			alert_outer.style.WebkitTranstion = 'all' + animation_delay + 's ease';
			alert_outer.style.transtion = 'all' + animation_delay + 's ease';
		});
	}
	
	function alert_hide(callback) {
		alert_outer.style.top = '-' + alert_outer.offsetHeight - 5 + 'px';
		setTimeout(function() {
			if(shadow) {
				alert_outer.style.boxShadow = '';
			}
			
			alert_outer.style.MozTransition = '';
			alert_outer.style.webkitTransition = '';
			alert_outer.style.transtion = '';
			alert_outer.style.top = '-1000px';
			
			if(callback) {
				callback();
			}
				
			
		}, (animation_delay * 1000 + 10) );
	}
		
	var confirm_outer = document.createElement('div');
	confirm_outer.id  = confirm_outer_id;
	confirm_outer.style.position = 'fixed';
	confirm_outer.style.top = '0';
	confirm_outer.style.left = '0';
	confirm_outer.style.zIndex = '99999996';
	confirm_outer.style.height = 'auto';
	confirm_outer.style.width = '100%';
	confirm_outer.style.display = 'none';
	confirm_outer.style.textAlign = 'center';
	
	var confirm_background = document.createElement('div');
    
    confirm_background.onclick = function() {
        if(background_click_dismiss) {
            confirm_hide();
        }       
    }
    var confirm_yes = document.createElement('div');
    confirm_yes.style.id  = confirm_yes_id;
    confirm_yes.style.cssFloat = 'left';
    confirm_yes.style.height = '50px';
    confirm_yes.style.lineHeight = '50px';
    confirm_yes.style.width = '50%';
    confirm_yes.style.cursor = 'pointer';
    confirm_yes.style.background = confirm_and_input_color_yes_background;
    confirm_outer.appendChild(confirm_yes);
    
    var confirm_no = document.createElement('div');
    confirm_no.id = confirm_no_id;
    confirm_no.style.cssFloat = 'right';
    confirm_no.style.height = '50px';
    confirm_no.style.lineHeight = '50px';
    confirm_no.style.width  = '50%'
    confirm_no.style.cursor = 'pointer';
    confirm_no.style.background = confirm_and_input_color_no_background;
    confirm_no.style.onclick = function(){
        confirm_hide();
    };
    confirm_outer.appendChild(confirm_no);
    
	var confirm_text = document.createElement('span');
	confirm_text.id = confirm_yes_id;
	confirm_text.style.color = confirm_and_input_color_text; 
    //设置友好的字体。
	if(window.innerWidth <= font_change_screen_width) {
		confirm_text.style.fontSize = font_size_small;
	} else {
		confirm_text.style.fontSize = font_size_big;
	}
    
    
    
    var confirm_yes_text = document.createElement('span');
    confirm_yes_text.id = confirm_yes_text_id;
    confirm_yes_text.style.color = confirm_and_input_color_yes_background;
    
    if(window.innerHeight <= font_change_screen_width) {
      confirm_yes_text.style.fontSize = font_size_small;
    } else {
        confirm_yes_text.style.fontSize = font_size_big;
    }
    //监听窗口变大或变小的时间。
    //bind会创建创建一个函数，当这个函数调用的时候，它的this关键字被设置成传入的值。
    //就是传入到bind的参数。
    //这里将resizeListener作为回调函数传给debounce.
    //true表示所有指定的resize事件都会指定到debounce回调函数。
    window.addEventListener('resize',debounce(resizeListener.bind(null,confirm_yes_text),debounce_time),true);
    confirm_yes.appendChild(confirm_yes_text);
    
    
    var confirm_no_text = document.createElement('span');
    confirm_no_text.id = confirm_no_text_id;
    confirm_no_text.style.color = confirm_and_input_color_no_text;
    
    if(window.innerWidth <= font_change_screen_width) {
        confirm_no_text.style.fontSize = font_size_small;
    } else {
        confirm_no_text.style.fontSize = font_size_big;
    }
    window.addEventListener("resize",debounce(resizeListener.bind(null,confirm_no_text),debounce_time),true);
    confirm_no.appendChild(confirm_no_text);
    
    
    //
    document.body.appendChild(confirm_outer);
    document.body.appendChild(confirm_background);
   
	
	function confirm(title,yes_text,no_text,yes_callback) {
		document.activeElement.blur();
		
		if(alert_is_showing) {
			clearTimeout(alert_timeout_1);
			clearTimeout(alert_timeout_2);
			
			alert_hide(function() {
					confirm_show(title,yes_text,no_text,yes_callback);
			});
		} else {
			confirm_show(title,yes_text,no_text,yes_callback);
		}
	}
	
	function confirm_show(title,yes_text,no_text,yes_call_back) {
		scroll_disable();
		
		confirm_yes.onclick = function() {
			confirm_hide();
			setTimeout(function() {
				yes_call_back()
			},(animation_delay * 1000 ) + 10);
		}
		
		function confirm_show_inner() {
		    confirm_text.innerHTML = title;
            confirm_yes_text.innerHTML = yes_text;
            confirm_no_text.innerHTML = no_text;
            
            confirm_outer.style.top = '-10000px';
            confirm_outer.style.display = 'table';
            confirm_outer.style.top = '-' + confirm_outer.offsetHeight - 5 + 'px';
            confirm_background.style.display = 'block';
            
            setTimeout(function() {
                if(shadow) {
                    confirm_outer.style.boxShadow = '0px 0px 10px 0px rgba(0,0,0,0.5)';
                    confirm_outer.style.MozTransition = 'all ' +  animation_delay + 's ease';
                    confirm_outer.style.webkitTransition = 'all ' + animation_delay + 's ease';
                    confirm_outer.style.transition = 'all ' + animation_delay + 's ease';

                    confirm_outer.style.top = 0;
                    confirm_outer.style.opacity = '0.75';
                    setTimeout(function() {
                        confirm_is_showing = true;
                    },(animation_delay * 1000) + 10);
                    
                }
                
            },20);
        }
        
        if(confirm_is_showing) {
            confirm_hide();
            setTimeout(function() {
                confirm_show_inner();
            },(animation_delay * 1000) + 10);
        }
	} // end of confirm_show
    
    function confirm_hide() {
        confirm_outer.style.top = '-' + confirm_outer.offsetHeight - 5 + 'px';
        confirm_background.style.opacity = '0';
        
        setTimeout(function(){
            if(shadow) {
                confirm_outer.style.boxShadow = '';
            }
            
            confirm_outer.style.MozTransition = "";
            confirm_outer.style.webkitTranstion = '';
            confirm_outer.style.transition = "";
            confirm_outer.style.display = 'none';
            confirm_outer.style.top = ' - 10000px';
            scroll_enable();
            confirm_is_showing = false;
         
        },(animation_delay) * 1000 + 10);
        
    } // end of confirm_hide
}
