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
	QSpacerItem     *m_spacer1;
	QLabel          *m_labelIcon;
	QSpacerItem     *m_spacer2;
	QLabel          *m_labelTitle;
	QSpacerItem     *m_spacer3;

	void setupUi(QWidget *widget);
};

size_t urand(size_t max)
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
	if(widget->objectName().size() == 0) /*result of objectName() ref--*/ /* widget??(=R1 not R0) */ /* unlikely */
	{
		widget->setObjectName(QString::fromUtf8("IconPowerView")); /*ref--*/
	}

	widget->resize(QSize(600, 800));
	widget->setStyleSheet(QString::fromUtf8("QWidget { color: black; background: white; }")); /*ref--*/

	QVBoxLayout *layout = new QVBoxLayout(widget);
	this->m_layout = layout; // (u32*)this[0] = layout
	layout->setSpacing(0);
	layout->setObjectName("verticalLayout"); /*ref--*/

	// make sure objects for caller of this... or die!

	// SleepStatusView <...< QWidget
	SleepStatusView *status = new SleepStatusView(widget); /*size 0x20*/
	this->m_status = status; // (u32*)this[1] = layout
	status->setObjectName("statusBar"); /*ref--*/

	QSpacerItem *spacer = new QSpacerItem(20, 210);/*size0x24*/
	// (u32*)spacer[0] = &vptr[2] ?
	// (u32*)spacer[1:] = [0,0x14,0xd2,1,0,0,-1,-1]
	this->m_spacer1 = spacer; // (u32*)this[2] = spacer

	//QFlags windowtype(0);
	QLabel *labelIcon = new QLabel(widget, /*&windowtype*/0);
	this->m_labelIcon = labelIcon; // (u32*)this[3] = labelIcon
	labelIcon->setObjectName(QString::fromUtf8("icon")); /*ref--*/

	QSpacerItem *spacer2 = new QSpacerItem(20, 80);/*size0x24*/
	// (u32*)spacer2[0] = &vptr[2] ?
	// (u32*)spacer2[1:] = [0,0x14,0x50,1,0,0,-1,-1]
	this->m_spacer2 = spacer2; // (u32*)this[4] = spacer2

	//QFlags windowtype2(0);
	QLabel *labelTitle = new QLabel(widget, /*&windowtype2*/0); /*size0x14*/
	this->m_labelTitle = labelTitle; // (u32*)this[5] = labelTitle
	labelTitle->setObjectName(QString::fromUtf8("title")); /*ref--*/

	QSpacerItem *spacer3 = new QSpacerItem(20, 40, QSizePolicy::Expanding); /*size0x24*/
	// (u32*)spacer3[0] = &vptr[2] ?
	// (u32*)spacer3[1:] = [0,0x14,0x28,0x71,0,0,-1,-1]
	this->m_spacer3 = spacer3; // (u32*)this[6] = spacer3

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

		labelIcon->setPixmap(QPixmap(QString::fromUtf8(picfile), NULL, 0)); /*ref-- after setPixmap*/
		labelIcon->setAlignment(Qt::AlignCenter);
		layout->addWidget(labelIcon, 0, 0);

		globfree(&g);
	} else {
		// defaults

		layout->setContentsMargins(20, 20, 20, 20);

		status->setMinimumSize(0, 50);
		status->setMaximumSize(0xFFFFFF, 50);
		status->setStyleSheet(QString::fromUtf8("background: none;")); /*ref--*/
		//QFlags align(0);
		layout->addWidget(status, 0, /*&align*/0);

		layout->addItem(spacer); // Really?

		//QFlags iconvflag(0);
		/* this pixmap seems on stack, not ptr... */
		QPixmap pixmap(QString::fromUtf8(":/images/dialogs/ereader-sleeping-black.png"), NULL, /*&iconvflag*/0); /*ref-- after setPixmap*/
		labelIcon->setPixmap(pixmap);
		//QFlags align2(0x84); // 0x84 = Qt::AlignCenter
		labelIcon->setAlignment(/*&align2*/Qt::AlignCenter);
		//QFlags align3(0);
		layout->addWidget(labelIcon, 0, /*&align3*/0);

		layout->addItem(spacer2); // Really?

		labelTitle->setStyleSheet(QString::fromUtf8("font-size: 44px;")); /*ref--*/
		//QFlags align4(0x84);
		labelTitle->setAlignment(/*&align4*/Qt::AlignCenter);
		//QFlags align5(0);
		layout->addWidget(labelTitle, /*&align5*/0);

		layout->addItem(spacer3); // Really?

		labelIcon->setText(/*QString::shared_null*/QString()); /*ref++; ref--*/
		labelTitle->setText(QCoreApplication::translate("IconPowerView", "Sleep Mode", 0, /*1*/QCoreApplication::UnicodeUTF8)); /*translated ref--*/
	}

	QMetaObject::connectSlotsByName(widget);
}
