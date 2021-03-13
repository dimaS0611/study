#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <locale.h>

void trace(const char* msg)
{
	printf("%s\n", msg);
}

void wait_any_key()
{
	while (!_kbhit()) {
		Sleep(1);
	}
}

void pressAnyKey()
{
	trace("Press any key...");
	wait_any_key();
}

typedef BOOLEAN(__cdecl *tget_author)(char* Str, int maxLen, DWORD* pBytesWritten);
typedef BOOLEAN(__cdecl *tget_description)(char* Str, int maxLen, DWORD* pBytesWritten);
typedef void(__cdecl *texec)();

struct Plugin
{
    HMODULE lib;
    tget_author get_author;
    tget_description get_desc;
    texec exec;
};

char plugins[256];

BOOL plug_init(struct Plugin* plug, const char* filename)
{
    char path[256];
    strncpy_s(path, 255, plugins, 255);
    strncat_s(path, 255, filename, 255);

    plug->lib = LoadLibraryA(path);
    if (plug->lib < (HMODULE)32)
        return FALSE;

    (FARPROC)plug->get_author = GetProcAddress(plug->lib, "get_author");
    (FARPROC)plug->get_desc = GetProcAddress(plug->lib, "get_description");
    (FARPROC)plug->exec = GetProcAddress(plug->lib, "exec");

    return (plug->get_author && plug->get_desc && plug->exec);
}

void plug_free(struct Plugin* plug)
{
    if (plug->lib >= (HMODULE)32)
        FreeLibrary(plug->lib);
}

void plug_exec(struct Plugin* plug, BOOL exec)
{
    char str[256];
    if (plug->get_author(str, 255, NULL))
        trace(str);
    if (plug->get_desc(str, 255, NULL))
		trace(str);

	if(exec)
		plug->exec();
}

int main(int argc, char* argv[])
{
    {
        strncpy_s(plugins, 255, argv[0], 255);

        char* p = strstr(plugins, "\\");
        while (p)
        {
            p++;
            char* q = strstr(p, "\\");
            if (!q)
            {
                *p = 0;
                break;
            }
            p = q;
        }

        strncat_s(plugins, 255, "plugins\\", 255);
    }

	struct Plugin plugin1;
	struct Plugin plugin2;
	BOOL pl1 = FALSE, pl2 = FALSE;

	BOOL lang_ru;
	
	setlocale(LC_ALL, "Russian");

	printf("Chose the languge:\n");
	printf("%s", "\tEnglish - '0'\n");
	printf("%s", "\tРусский - '1'\n");

	scanf_s("%i", &lang_ru);

	BOOL menu = TRUE;

	while (menu)
	{
		if (!lang_ru)
		{
			printf("%s\n", "Choose the option:");
			printf("%s\n", "1 - Load plugins");
			printf("%s\n", "2 - Unload plugins");
			printf("%s\n", "3 - Show info about loaded plugins");
			printf("%s\n", "4 - Execute plugins");
			printf("%s\n", "5 - Clean console");
			printf("%s\n", "6 - Exit");
		}
		else
		{
			printf("%s\n", "Выберете опцию:");
			printf("%s\n", "1 - Загрузить плагины");
			printf("%s\n", "2 - Выгрузить плагины");
			printf("%s\n", "3 - Показать информацию о загруженных плагинах");
			printf("%s\n", "4 - Выполнить плагины");
			printf("%s\n", "5 - Очистить консоль");
			printf("%s\n", "6 - Выход");
		}

		BOOL options = TRUE;
		int choisePl = 1;
		int choise = 1;

		while (options)
		{
			if (lang_ru)
				printf("%s", "\nОпция:\t");
			else
				printf("%s", "\nOption:\t");

			scanf_s("%d", &choise);

			switch (choise)
			{
			case 1:
			{
				pl1 = plug_init(&plugin1, "plugin1.dll");
				pl2 = plug_init(&plugin2, "plugin2.dll");

				if (pl1 && pl2)
				{
					if (lang_ru)
						printf("%s", "\nПлагины загружены\n");
					else
						printf("%s", "\nPlagins are loaded\n");
				}	
					
				options = FALSE;
				break;
			}

			case 2:
			{
				plug_free(&plugin1);
				plug_free(&plugin2);

				pl1 = FALSE;
				pl2 = FALSE;

				if (lang_ru)
					printf("%s", "\nПлагины выгружены\n");
				else
					printf("%s", "\nPlagins are unloaded\n");

				options = FALSE;
				break;
			}

			case 3:
				if (pl1 && pl2)
				{
					plug_exec(&plugin1, FALSE);
					plug_exec(&plugin2, FALSE);
				}
				else
				{
					if (lang_ru)
						printf("%s", "\nПлагины выгружены. Невозможно выполнить!\n");
					else
						printf("%s", "\nPlagins are unloaded. Unable to execute!\n");
				}

				options = FALSE;
				break;
			
			case 4:
				if (pl1 && pl2) {
					if (lang_ru)
						printf("%s", "\nВведите номер плагина(1, 2): ");
					else
						printf("%s", "\nEnter the number of plugin (1, 2): ");

					scanf_s("%d", &choisePl);

					if (choisePl == 1)
					{
						trace("\nplugin1:\n");
						plug_exec(&plugin1, TRUE);
					}
					if (choisePl == 2)
					{
						trace("\nplugin2:\n");
						plug_exec(&plugin2, TRUE);
					}
					else
					{
						if (lang_ru)
							printf("%s", "\nНеверный номер плагина\n");
						else
							printf("%s", "\nIncorrect number of plugin\n");
					}
				}
				else
				{
					if (lang_ru)
						printf("%s", "\nПлагины выгружены. Невозможно выполнить!\n");
					else
						printf("%s", "\nPlagins are unloaded. Unable to execute!\n");

				}
				options = FALSE;
				break;
			case 5:
				system("cls");
				options = FALSE;
				break;
			case 6:
				plug_free(&plugin1);
				plug_free(&plugin2);

				if (lang_ru)
					printf("%s", "\nПлагины выгружены. Работа завершена!\n");
				else
					printf("%s", "\nPlagins are unloaded. Work is complete!\n");

				options = FALSE;
				menu = FALSE;
				break;
			default:
				if (lang_ru)
					printf("%s\n\n", "Некорректный выбор.\n");
				else
					printf("%s\n\n", "Incorrect choose.\n");
				break;
			}
		}
	}

    
	plug_free(&plugin1);
	plug_free(&plugin2);

	pressAnyKey();
}
