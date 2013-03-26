#include <QWidget>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QSizePolicy>
#include <QCoreApplication>
#include <QMetaObject>
//#include <QFlags>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <glob.h>

class SleepStatusView : public QWidget /*guess!*/
{
	char dummy[0x0C]; // QWidget+0x0C = 0x20
	/* dummy */

public:
	SleepStatusView(QWidget*);
};

class Ui_IconPowerView /* size 0x1C */
{
	QVBoxLayout     *m_layout;
	SleepStatusView *m_status;
	QWidget         *m_spacer1;
	QLabel          *m_labelIcon;
	QWidget         *m_spacer2;
	QHBoxLayout     *m_hlayout;
	QLabel          *m_pwricon;
	QLabel          *m_labelTitle;
	QSpacerItem     *m_spacer3;

	void setupUi(QWidget *widget);
};

static size_t urand(size_t max)
{
	// TODO more good rand() please!
	// TODO size_t!?
	int fd;
	char buf[sizeof(unsigned int)]; // XXX sizeof!
	double var;

	if((fd = open("/dev/urandom", O_RDONLY)) < 0)
	{
		return 0; // FIXME
	}
	read(fd, buf, sizeof(buf));
	var = (double)(*((unsigned int*)buf)) * max / UINT_MAX;
	close(fd);

	return (size_t)var;
}

/* R0 for this(?) but not used at all */
/* override weak */
void Ui_IconPowerView::setupUi(QWidget *widget)
{
	//QString/*?*/ str;
	//if(str.objectName()[8] == 0) /*ref--*/
	//if(widget->objectName().size() == 0) /*result of objectName() ref--*/ /* widget??(=R1 not R0) */ /* unlikely */
	if(widget->objectName().isEmpty()) /*result of objectName() ref--*/ /* widget??(=R1 not R0) */ /* unlikely */
	{
		//widget->setObjectName(QString::fromUtf8("IconPowerView")); /*ref--*/ -> implicit "fromUtf8"
		widget->setObjectName("IconPowerView"); /*ref--*/
	}

	widget->resize(QSize(600, 800));
	widget->setStyleSheet("QWidget { color: black; background: white; }"); /*ref--*/

	QVBoxLayout *layout = new QVBoxLayout(widget); /*size 0x10*/
	this->m_layout = layout; // (u32*)this[0] = layout
	layout->setSpacing(0);
	// layout->setContentsMargins(20, 20, 20, 20); // set later.
	layout->setObjectName("verticalLayout"); /*ref--*/

	// make sure objects for caller of this... or die!

	// SleepStatusView <...< QWidget
	SleepStatusView *status = new SleepStatusView(widget); /*size 0x20*/
	this->m_status = status; // (u32*)this[1] = layout
	status->setObjectName("statusBar"); /*ref--*/
	status->setStyleSheet("* { background: none; min-height: 50px; max-height: 50px; } [deviceCodeName=\"kraken\"] { min-height: 62px; max-height: 62px; }");

	QWidget *spacer1 = new QWidget(widget, /*QFlags*/0); /*size 0x14*/
	spacer1->setObjectName("verticalSpacer_2");
	spacer1->setStyleSheet("* { min-height: 123px; max-height: 123px; } [deviceCodeName=\"kraken\"] { min-height: 158px; max-height: 158px; }");
	this->m_spacer1 = spacer1; // (u32*)this[2] = spacer1

	QLabel *labelIcon = new QLabel(widget, /*QFlags<Qt::WindowType>*/0); /*size 0x14*/
	this->m_labelIcon = labelIcon; // (u32*)this[3] = labelIcon
	labelIcon->setObjectName(QString::fromUtf8("icon")); /*ref--*/
	labelIcon->setStyleSheet("* {\n\tqproperty-pixmap: url(:/images/dialogs/ereader-sleeping-white-trilogy.png);\n}\n[deviceCodeName=\"kraken\"] {\n\tqproperty-pixmap: url(:/images/dialogs/ereader-sleeping-white-kraken.png);\n}\n[deviceCodeName=\"pixie\"] {\n\tqproperty-pixmap: url(:/images/dialogs/ereader-sleeping-white-pixie.png);\n}\n[deviceCodeName=\"dragon\"] {\n\tqproperty-pixmap: none;\n}");
	labelIcon->setAlignment(/*QFlags<Qt::AlignmentFlag> 0x84*/Qt::AlignCenter);

	QWidget *spacer2 = new QWidget(widget, /*QFlags<Qt::WindowType>*/0); /*size 0x14*/
	spacer2->setObjectName("verticalSpacer_3");
	spacer2->setStyleSheet("* {\n\tmin-height: 60px;\n\tmax-height: 60px;\n}\n\n[deviceCodeName=\"kraken\"]  {\n\tmin-height: 77px;\n\tmax-height: 77px;\n}\n\n[deviceCodeName=\"dragon\"] {\n\tmin-height: 1070px;\n\tmax-height: 1070px;\n}");
	this->m_spacer2 = spacer2; // (u32*)this[4] = spacer2

	QHBoxLayout *hlayout = new QHBoxLayout(); /*size 0x10*/
	this->m_hlayout = hlayout; // (u32*)this[5] = hlayout
	hlayout->setObjectName("horizontalLayout");
	hlayout->setContentsMargins(-1, 0, -1, -1);

	QLabel *labelPowerIcon = new QLabel(widget, /*QFlags<Qt::WindowType>*/0); /*size0x14*/
	this->m_pwricon = labelPowerIcon; // (u32*)this[6] = labelPowerIcon
	labelPowerIcon->setObjectName("powerIcon");
	labelPowerIcon->setStyleSheet("* {\n\tqproperty-pixmap: none;\n\tmin-width: 0px;\n\tmax-width: 0px;\n\tmin-height: 0px;\n\tmax-height: 0px;\n}\n[deviceCodeName=\"dragon\"] {\n\tqproperty-pixmap: url(:/images/dialogs/global_sleep_power_dragon.png);\n\tmin-width: 56px;\n\tmax-width: 56px;\n\tmin-height: 56px;\n\tmax-height: 56px;\n\tpadding-left: 116px;\n\tpadding-right: 20px;\n\tqproperty-alignment: AlignLeft;\n}");

	QLabel *labelTitle = new QLabel(widget, /*QFlags<Qt::WindowType>*/0); /*size0x14*/
	this->m_labelTitle = labelTitle; // (u32*)this[7] = labelTitle
	labelTitle->setObjectName("title"); /*ref--*/
	labelTitle->setStyleSheet("* {\n\tfont-size: 44px;\n}\n\n[deviceCodeName=\"kraken\"] {\n\tfont-size: 55px;\n}\n\n[deviceCodeName=\"dragon\"] {\n\tfont-size: 46px;\n\tqproperty-alignment: AlignLeft;\n}");
	labelTitle->setAlignment(/*&align4*/Qt::AlignCenter);

	QSpacerItem *spacer3 = new QSpacerItem(20, 40, QSizePolicy::Expanding); /*size0x24*/
	// (u32*)spacer3[0] = &vptr[2] ?
	// (u32*)spacer3[1:] = [0,0x14,0x28,0x71,0,0,-1,-1]
	this->m_spacer3 = spacer3; // (u32*)this[8] = spacer3
	// call layout.vptr[+0x38] = virtual QSpacerItem spacerItem()?

	labelPowerIcon->setText(/*shared_null*/NULL);

	// kindle or not...
	char *picfile = NULL;
	glob_t g;
	const char *sleeppath, *sleepglob;

	sleeppath = getenv("HACK_SLEEP_PATH");
	if(sleeppath == NULL)
	{
		sleeppath = "/mnt/onboard/hack/sleep";
	}

	sleepglob = getenv("HACK_SLEEP_GLOB");
	if(sleepglob == NULL)
	{
		sleepglob = "*.png";
	}

	if(chdir(sleeppath) == 0) {
		if(glob(sleepglob, GLOB_NOSORT | GLOB_NOESCAPE, NULL, &g) == 0) {
			if(g.gl_pathc > 0) {
				size_t idx = urand(g.gl_pathc);
				picfile = g.gl_pathv[idx];
			}
		}
	}

	if(picfile)
	{
		layout->setContentsMargins(0, 0, 0, 0);

		//labelIcon->setPixmap(QPixmap(picfile, NULL, 0)); /*ref-- after setPixmap*/
		// setPixmap does not work on Kobo 2.4.0... Quick-Hack!
		labelIcon->setStyleSheet(QString("* {\n\tqproperty-pixmap: url(%1);\n}").arg(picfile));
		layout->addWidget(labelIcon, 0, 0);

		status->setVisible(false); // dont show small white rect at top-left.
		spacer1->setVisible(false);
		spacer2->setVisible(false);
		labelTitle->setVisible(false);

		globfree(&g);
	} else {
		// defaults

		layout->setContentsMargins(20, 20, 20, 20);

		layout->addWidget(status, 0, /*QFlags*/0);

		layout->addWidget(spacer1, 0, /*QFlags<Qt::AlignmentFlag>*/0);

		//QFlags iconvflag(0);
		/* this pixmap seems on stack, not ptr... */
		//QPixmap pixmap(QString::fromUtf8(":/images/dialogs/ereader-sleeping-black.png"), NULL, /*&iconvflag*/0); /*ref-- after setPixmap*/
		//labelIcon->setPixmap(pixmap);
		layout->addWidget(labelIcon, 0, /*QFlags<Qt::AlignmentFlag>*/0);

		layout->addWidget(spacer2, 0, 0);

		hlayout->addWidget(labelPowerIcon, 0, 0);

		hlayout->addWidget(labelTitle, 0, 0);

		layout->addLayout(hlayout, 0);

		layout->addItem(spacer3); // Really?

		labelTitle->setText(QCoreApplication::translate("IconPowerView", "Sleep Mode", 0, /*1*/QCoreApplication::UnicodeUTF8)); /*translated ref--*/
	}

	QMetaObject::connectSlotsByName(widget);
}
