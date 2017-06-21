#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WHBoxLayout>
#include <Wt/WPushButton>
#include <Wt/WTabWidget>
#include <Wt/WText>
#include <Wt/WVBoxLayout>


class TestApplication : public Wt::WApplication
{
public:
	TestApplication(const Wt::WEnvironment& environment);

protected:
	void AddContentButtonClicked();

private:
	Wt::WVBoxLayout* m_result_layout;
};

TestApplication::TestApplication(const Wt::WEnvironment& environment)
: Wt::WApplication(environment)
{
	useStyleSheet(Wt::WLink("testcase.css"));

	Wt::WVBoxLayout* root_vbox = new Wt::WVBoxLayout();
	root()->setLayout(root_vbox);
	root()->setStyleClass("page");

	//Header
	Wt::WContainerWidget* header_container = new Wt::WContainerWidget();
	Wt::WHBoxLayout* header_layout = new Wt::WHBoxLayout();
	header_container->setLayout(header_layout);
	header_container->setStyleClass("testcase-header");
	header_layout->addWidget(new Wt::WText("header"));
	root_vbox->addWidget(header_container);

	//Tabs
	Wt::WContainerWidget* tabs_container = new Wt::WContainerWidget();
	Wt::WHBoxLayout* tabs_hbox = new Wt::WHBoxLayout();
	tabs_container->setLayout(tabs_hbox);

	Wt::WTabWidget* tab_widget = new Wt::WTabWidget();
	Wt::WContainerWidget* search_container = new Wt::WContainerWidget();
	Wt::WVBoxLayout* search_layout = new Wt::WVBoxLayout();
	search_container->setLayout(search_layout);

	Wt::WContainerWidget* searchform_container = new Wt::WContainerWidget();
	Wt::WHBoxLayout* searchform_hbox = new Wt::WHBoxLayout();
	searchform_container->setLayout(searchform_hbox);

	Wt::WPushButton* search_button = new Wt::WPushButton("Add content");
	search_button->clicked().connect(this, &TestApplication::AddContentButtonClicked);
	searchform_hbox->addWidget(search_button);

	search_layout->addWidget(searchform_container);

	Wt::WContainerWidget* result_container = new Wt::WContainerWidget();
	m_result_layout = new Wt::WVBoxLayout();
	result_container->setLayout(m_result_layout);
	search_layout->addWidget(result_container);

	tab_widget->addTab(search_container, "Content");

	Wt::WContainerWidget* tmp_tab_container = new Wt::WContainerWidget(); //stretch and tabwidget doesn't mix very well. Wrap tabwidget in a containerwidget
	tmp_tab_container->addWidget(tab_widget);
	tabs_hbox->addWidget(tmp_tab_container);
	root_vbox->addWidget(tabs_container, 1); //Header and footer is static. tabs_container should take rest of available space

	//Footer
	Wt::WContainerWidget* footer_container = new Wt::WContainerWidget();
	Wt::WHBoxLayout* footer_layout = new Wt::WHBoxLayout();
	footer_container->setLayout(footer_layout);
	footer_container->setStyleClass("testcase-footer");
	footer_layout->addWidget(new Wt::WText("footer"));
	root_vbox->addWidget(footer_container);
}

void TestApplication::AddContentButtonClicked()
{
	for (int i=0; i<15; i++)
		m_result_layout->addWidget(new Wt::WText("Dummy"));
}



Wt::WApplication* createApplication(const Wt::WEnvironment& env)
{
	return new TestApplication(env);
}

int main(int argc, char** argv)
{
	return Wt::WRun(argc, argv, &createApplication);
}
