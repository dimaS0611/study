$(document).ready(function () {
	// по€вление/затухание кнопки #back-top
	$(function () {
		// пр€чем кнопку #back-top
		$("#back-top").hide();

		$(window).scroll(function () {
			if ($(this).scrollTop() > 100) {
				$("#back-top").fadeIn();
			} else {
				$("#back-top").fadeOut();
			}
		});

		// при клике на ссылку плавно поднимаемс€ вверх
		$("#back-top a").click(function () {
			$("body,html").animate({
				scrollTop: 0
			}, 800);
			return false;
		});
	});
});