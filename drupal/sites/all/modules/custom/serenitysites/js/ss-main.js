(function ($) {
  Drupal.behaviors.serenity = {
    attach: function (context, settings) {
	  $('.list-modal-close').click(function(){
	  	jQuery('.list-modal').css('display', 'none');
	  });

	  $('.show-more-modal').click(function(){
	  	jQuery(this).parent().find('.list-modal').css('display', 'block');
	  });
	}
  }
})(jQuery);

