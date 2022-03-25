#include "io/read_image.h"
#include "io/write_image.h"
#include "parser.h"
#include "filter_applier.h"

int main(int argc, const char *argv[]) {

    // examples/example.bmp output.bmp -crop 100 100 -blur 4.5 -neg
    // examples/example.bmp output.bmp -crop 1024 1024 -blur 4.5 -neg
    try {
        std::vector<std::pair<std::string, std::vector<float>>> arguments = ParseCmdLine(argc, argv);
        Image input = ReadImage(argv[1]);
        FilterApplier applier(arguments);
        Image output = applier.Apply(input);
        WriteImage(output, argv[2]);
    } catch (const NoInputFilePath& e) {
        // :
        std::cout << e.what() << std::endl;
    } catch (const NoOutputFilePath& e) {
        // : examples/example.bmp
        std::cout << e.what() << std::endl;
    } catch (const NoAppliedFilters& e) {
        // : examples/example.bmp output.bmp
        std::cout << e.what() << std::endl;
    } catch (const WrongArgumentSyntax& e) {
        // : examples/example.bmp output.bmp neg
        std::cout << e.what() << std::endl;
    } catch (const WrongInputFilePath& e) {
        // : wrong_path.bmp output.bmp -neg
        std::cout << e.what() << std::endl;
    } catch (const WrongFileFormat& e) {
        // : examples/wrong_format.png output.bmp -neg
        std::cout << e.what() << std::endl;
    } catch (const WrongBmpFormat& e) {
        // : examples/wrong_bmp.bmp output.bmp -neg
        std::cout << e.what() << std::endl;
    } catch (const WrongFilterName& e) {
        // : examples/example.bmp output.bmp -negative
        std::cout << e.what() << std::endl;
    } catch (const WrongAmountOfFilterArguments& e) {
        // : examples/example.bmp output.bmp -neg 1
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Error happened. Maybe the output path is incorrect." << std::endl;
    }

    return 0;
}
