$(document).ready(function () {
	// ���������/��������� ������ #back-top
	$(function () {
		// ������ ������ #back-top
		$("#back-top").hide();

		$(window).scroll(function () {
			if ($(this).scrollTop() > 100) {
				$("#back-top").fadeIn();
			} else {
				$("#back-top").fadeOut();
			}
		});

		// ��� ����� �� ������ ������ ����������� �����
		$("#back-top a").click(function () {
			$("body,html").animate({
				scrollTop: 0
			}, 800);
			return false;
		});
	});
});