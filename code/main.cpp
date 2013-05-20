#include "notes.h"

using namespace Frame;

int main(void)
{
	Article a("test.txt", "test", "Ceci est un article de test.");

	cout << a.getTitle() \
	<< "\n" << a.getText() \
	<< "\n";

	a.addTag("test");
	a.addTag("test");
	a.addTag("Article");

	cout << "\n" << a.getTags() \
	<< "\nhasTag(\"\"): " << a.hasTag("") \
	<< "\n";

    return 0;
}
