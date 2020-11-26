#include <iomanip>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

class boyfriend {
public:
  std::string name = {};
  double education = 0;
  double force = 0;
  double appearance = 0;
  double character = 0;

  boyfriend(std::string name, double a, double b, double c, double d) {
    this->name = std::move(name);
    education = a;
    force = d;
    appearance = c;
    character = b;
  }
};

class vector_boyfriend {
public:
  std::vector<boyfriend> boyfriends = {};
  double max_education = 0;
  double min_education = 10;
  double max_force = 0;
  double min_force = 10;
  double max_appearance = 0;
  double min_appearance = 10;
  double max_character = 0;
  double min_character = 10;

  vector_boyfriend(boyfriend sergey, boyfriend aleksandr, boyfriend vladimir,
                   boyfriend anatoliy) {
    boyfriends = {std::move(sergey), std::move(aleksandr), std::move(vladimir),
                  std::move(anatoliy)};
    for (auto &it : boyfriends) {
      if (it.education > max_education)
        max_education = it.education;
      if (it.education < min_education)
        min_education = it.education;
      if (it.force > max_force)
        max_force = it.force;
      if (it.force < min_force)
        min_force = it.force;
      if (it.appearance > max_appearance)
        max_appearance = it.appearance;
      if (it.appearance < min_appearance)
        min_appearance = it.appearance;
      if (it.character > max_character)
        max_character = it.character;
      if (it.character < min_character)
        min_character = it.character;
    }
  }
};

void normalization_task_1(vector_boyfriend &guys) {
  for (auto &it : guys.boyfriends) {
    it.force = (it.force - guys.min_force) / (guys.max_force - guys.min_force);
    it.appearance = (it.appearance - guys.min_appearance) /
                    (guys.max_appearance - guys.min_appearance);
    it.character = (it.character - guys.min_character) /
                   (guys.max_character - guys.min_character);
  }
}

boyfriend search_normal_kid_task_1(
    const vector_boyfriend &guys,
    const std::map<std::string, double> &minimum_tolerance) {
  std::vector<boyfriend> passed_verification = {};
  for (auto &it : guys.boyfriends) {
    if (it.force >= minimum_tolerance.at("force") &&
        it.appearance >= minimum_tolerance.at("appearance") &&
        it.character >= minimum_tolerance.at("character"))
      passed_verification.push_back(it);
  }
  if (passed_verification.size() == 1) {
    return passed_verification[0];
  }
  if (passed_verification[0].education > passed_verification[1].education) {
    return passed_verification[0];
  } else {
    return passed_verification[1];
  }
}

void print_task_1_part1(const vector_boyfriend &guys) {
  std::cout
      << "============================TASK1================================="
      << std::endl;
  std::cout << "Weights:" << std::endl
            << std::setw(14) << std::right << "education" << std::setw(11)
            << std::right << "character" << std::setw(12) << std::right
            << "appearance" << std::setw(7) << std::right << "force"
            << std::endl;
  std::cout << std::setw(13) << 8 << std::setw(11) << 6 << std::setw(12) << 4
            << std::setw(7) << 2 << std::endl
            << std::endl;
  std::cout << "Weights normal:" << std::endl
            << std::setw(14) << std::right << "education" << std::setw(11)
            << std::right << "character" << std::setw(12) << std::right
            << "appearance" << std::setw(7) << std::right << "force"
            << std::endl;
  std::cout << std::setw(13) << 0.4 << std::setw(11) << 0.3 << std::setw(12)
            << 0.2 << std::setw(7) << 0.1 << std::endl
            << std::endl;
  std::cout << "Major rate: education" << std::endl << std::endl;

  std::cout << std::setw(25) << std::right << "education" << std::setw(11)
            << std::right << "character" << std::setw(12) << std::right
            << "appearance" << std::setw(7) << std::right << "force"
            << std::endl;
  for (auto &it : guys.boyfriends) {
    const int length = 24;
    std::cout << it.name << std::setw(length - int(it.name.size()))
              << it.education << std::setw(11) << it.character << std::setw(12)
              << it.appearance << std::setw(7) << it.force << std::endl
              << std::endl;
  }
}

void print_task_1_part2(
    const vector_boyfriend &guys,
    const std::map<std::string, double> &minimum_tolerance) {
  std::cout << "normalizes:" << std::endl;
  std::cout << std::setw(25) << std::right << "education" << std::setw(11)
            << std::right << "character" << std::setw(12) << std::right
            << "appearance" << std::setw(7) << std::right << "force"
            << std::endl;
  for (auto &it : guys.boyfriends) {
    const int length = 24;
    std::cout << it.name << std::setw(length - int(it.name.size()))
              << it.education << std::setw(11) << it.character << std::setw(12)
              << it.appearance << std::setw(7) << it.force << std::endl
              << std::endl;
  }
  std::cout << std::endl << std::endl;
  std::cout << "education  |  it's major rate" << std::endl;
  std::cout << "character  |  not less than "
            << minimum_tolerance.at("character") << std::endl;
  std::cout << "appearance |  not less than "
            << minimum_tolerance.at("appearance") << std::endl;
  std::cout << "force      |  not less than " << minimum_tolerance.at("force")
            << std::endl
            << std::endl;
  std::cout << "best man: "
            << search_normal_kid_task_1(guys, minimum_tolerance).name
            << std::endl;
  std::cout
      << "=================================================================="
      << std::endl;
}

void task_1(vector_boyfriend guys) {
  std::map<std::string, double> minimum_tolerance = {
      {"force", 0.1 * guys.max_force},
      {"appearance", 0.1 * guys.max_appearance},
      {"character", 0.2 * guys.min_character}};
  print_task_1_part1(guys);
  normalization_task_1(guys);
  print_task_1_part2(guys, minimum_tolerance);
}

void task_2(vector_boyfriend guys) {
  std::pair<double, double> the_point_of_utopia = {};
  if (guys.max_education > guys.max_character) {
    the_point_of_utopia.first = guys.max_education;
    the_point_of_utopia.second = guys.max_education;
  } else {
    the_point_of_utopia.first = guys.max_character;
    the_point_of_utopia.second = guys.max_character;
  }
  boyfriend best_man = guys.boyfriends[0];
  for (size_t i = 1; i < 4; ++i) {
    if ((std::abs(the_point_of_utopia.first - guys.boyfriends[i].education) +
         std::abs(the_point_of_utopia.second - guys.boyfriends[i].character)) <
        (std::abs(the_point_of_utopia.first - best_man.education) +
         std::abs(the_point_of_utopia.second - best_man.character))) {
      best_man = guys.boyfriends[i];
    }
  }
  std::cout
      << "===============================TASK2=============================="
      << std::endl;
  std::cout << "x-coordinate = education | y-coordinate = character"
            << std::endl;
  std::cout << guys.boyfriends[0].name << "          "
            << "(" << guys.boyfriends[0].education << ","
            << guys.boyfriends[0].character << ")" << std::endl;
  std::cout << guys.boyfriends[1].name << "       "
            << "(" << guys.boyfriends[1].education << ","
            << guys.boyfriends[1].character << ")" << std::endl;
  std::cout << guys.boyfriends[2].name << "        "
            << "(" << guys.boyfriends[2].education << ","
            << guys.boyfriends[2].character << ")" << std::endl;
  std::cout << guys.boyfriends[3].name << "        "
            << "(" << guys.boyfriends[3].education << ","
            << guys.boyfriends[3].character << ")" << std::endl;
  std::cout << "best_man: " << best_man.name << std::endl;
  std::cout
      << "=================================================================="
      << std::endl;
}

void normalization_task_3(vector_boyfriend &guys) {
  double sum_education =
      guys.boyfriends[0].education + guys.boyfriends[1].education +
      guys.boyfriends[2].education + guys.boyfriends[3].education;
  double sum_character =
      guys.boyfriends[0].character + guys.boyfriends[1].character +
      guys.boyfriends[2].character + guys.boyfriends[3].character;
  double sum_appearance =
      guys.boyfriends[0].appearance + guys.boyfriends[1].appearance +
      guys.boyfriends[2].appearance + guys.boyfriends[3].appearance;
  double sum_force = guys.boyfriends[0].force + guys.boyfriends[0].force +
                     guys.boyfriends[1].force + guys.boyfriends[2].force +
                     guys.boyfriends[3].force;
  for (auto &it : guys.boyfriends) {
    it.education = it.education / sum_education;
    it.character = it.character / sum_character;
    it.appearance = it.appearance / sum_appearance;
    it.force = it.force / sum_force;
  }
}

std::vector<double>
vector_criteria_task3(const vector_boyfriend &guys,
                      const std::map<std::string, double> &weights_normal) {
  std::vector<double> vector_criteria = {0, 0, 0, 0};
  std::vector<std::vector<double>> matrix_criteria = {
      {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  for (auto i = 0; i < 4; ++i) {
    for (auto k = 1; k < 4; ++k) {
      double summ =
          ((guys.boyfriends[0].education - guys.boyfriends[1].education) *
               weights_normal.at("education") +
           (guys.boyfriends[0].character - guys.boyfriends[1].character) *
               weights_normal.at("character") +
           (guys.boyfriends[0].appearance - guys.boyfriends[1].appearance) *
               weights_normal.at("appearance") +
           (guys.boyfriends[0].force - guys.boyfriends[1].force) *
               weights_normal.at("force"));
      if (summ > 0) {
        matrix_criteria[i][k] = 1;
      } else if (summ == 0) {
        matrix_criteria[i][k] = 0.5;
      } else if (summ < 0) {
        matrix_criteria[i][k] = 0;
      }
    }
  }
  for (auto i = 0; i < 4; ++i) {
    vector_criteria[i] = matrix_criteria[i][0] + matrix_criteria[i][1] +
                         matrix_criteria[i][2] + matrix_criteria[i][3];
  }
  for (auto i = 0; i < 4; ++i) {
    vector_criteria[i] =
        vector_criteria[i] / (vector_criteria[0] + vector_criteria[1] +
                              vector_criteria[2] + vector_criteria[3]);
  }
  return vector_criteria;
}

std::vector<double>
matrix_x_vector_task3(vector_boyfriend &guys,
                      std::vector<double> &vector_criteria) {
  std::vector<double> acceptable = {0, 0, 0, 0};
  for (auto i = 0; i < 4; ++i) {
    acceptable[i] = guys.boyfriends[i].education * vector_criteria[0] +
                    guys.boyfriends[i].character * vector_criteria[1] +
                    guys.boyfriends[i].appearance * vector_criteria[2] +
                    guys.boyfriends[i].force * vector_criteria[3];
  }
  return acceptable;
}

boyfriend
choice_of_an_alternative_task3_task4(const vector_boyfriend &guys,
                                     const std::vector<double> &acceptable) {
  int i = 0;
  double max = acceptable[0];
  for (auto k = 1; k < 4; ++k) {
    if (max < acceptable[k]) {
      max = acceptable[k];
      i = k;
    }
  }
  return guys.boyfriends[i];
}

void print_matrix_task3(const vector_boyfriend &guys) {
  std::cout << std::setw(25) << std::right << "education" << std::setw(11)
            << std::right << "character" << std::setw(12) << std::right
            << "appearance" << std::setw(7) << std::right << "force"
            << std::endl;
  for (auto &it : guys.boyfriends) {
    const int length = 24;
    std::cout << std::setprecision(2) << it.name
              << std::setw(length - int(it.name.size())) << it.education
              << std::setw(11) << it.character << std::setw(12) << it.appearance
              << std::setw(7) << it.force << std::endl
              << std::endl;
  }
}

void print_vector_task_3_task_4(const vector_boyfriend &guys,
                                const std::vector<double> &vec) {
  int k = 20;
  for (auto i = 0; i < 4; ++i) {
    std::cout << guys.boyfriends[i].name << std::right
              << std::setw(k - int(guys.boyfriends[i].name.size())) << vec[i]
              << std::endl;
  }
  std::cout << std::endl;
}

void task_3(vector_boyfriend guys,
            const std::map<std::string, double> &weights_normal) {
  std::cout
      << "============================TASK3================================="
      << std::endl;
  print_matrix_task3(guys);
  normalization_task_3(guys);
  std::vector<double> vector_criteria =
      vector_criteria_task3(guys, weights_normal);
  std::vector<double> acceptable = matrix_x_vector_task3(guys, vector_criteria);
  boyfriend best_guy = choice_of_an_alternative_task3_task4(guys, acceptable);
  std::cout << "normalizes: " << std::endl;
  print_matrix_task3(guys);
  std::cout << "gamma: " << std::endl;
  print_vector_task_3_task_4(guys, vector_criteria);
  std::cout << "result: " << std::endl;
  print_vector_task_3_task_4(guys, acceptable);
  std::cout << "best_guy: " << best_guy.name << std::endl;
  std::cout
      << "=================================================================="
      << std::endl;
}

std::vector<double>
matrix_x_vector_task_4(std::vector<std::vector<double>> matrix_result,
                       std::vector<double> vec_criteria) {
  std::vector<double> acceptable = {0, 0, 0, 0};
  for (auto i = 0; i < 4; ++i) {
    acceptable[i] = matrix_result[i][0] * vec_criteria[0] +
                    matrix_result[i][1] * vec_criteria[1] +
                    matrix_result[i][2] * vec_criteria[2] +
                    matrix_result[i][3] * vec_criteria[3];
  }
  return acceptable;
}

double sum_matrix_task4(const std::vector<std::vector<double>> &matrix) {
  double summ = 0;
  for (auto i = 0; i < 4; ++i) {
    for (auto k = 0; k < 4; ++k) {
      summ += matrix[i][k];
    }
  }
  return summ;
}

void print_matrix_task_4(const std::vector<std::vector<double>> &matrix) {
  std::cout << std::setw(25) << std::right << "education" << std::setw(11)
            << std::right << "character" << std::setw(12) << std::right
            << "appearance" << std::setw(7) << std::right << "force"
            << std::setw(7) << std::right << "summ" << std::setw(14)
            << std::right << "normalized" << std::endl;
  std::vector<std::string> categories = {"education", "character", "appearance",
                                         "force"};
  for (auto i = 0; i < 4; ++i) {
    const int length = 24;
    std::cout << std::setprecision(2) << categories[i]
              << std::setw(length - int(categories[i].size())) << matrix[i][0]
              << std::setw(11) << matrix[i][1] << std::setw(12) << matrix[i][2]
              << std::setw(7) << matrix[i][3] << std::setw(7)
              << matrix[i][0] + matrix[i][1] + matrix[i][2] + matrix[i][3]
              << std::setw(10)
              << (matrix[i][0] + matrix[i][1] + matrix[i][2] + matrix[i][3]) /
                     sum_matrix_task4(matrix)
              << std::endl
              << std::endl;
  }
}

void task_4(vector_boyfriend guys) {
  std::vector<std::vector<double>> matrix_education = {
      {1, 3, 9, 5}, {0.33, 1, 7, 3}, {0.11, 0.14, 1, 0.2}, {0.2, 0.33, 5, 1}};
  std::vector<std::vector<double>> matrix_character = {
      {1, 1, 1, 7}, {1, 1, 1, 7}, {1, 1, 1, 7}, {0.14, 0.14, 0.14, 1}};
  std::vector<std::vector<double>> matrix_appearance = {
      {1, 1, 0.14, 0.14}, {1, 1, 0.14, 0.14}, {7, 7, 1, 1}, {7, 7, 1, 1}};
  std::vector<std::vector<double>> matrix_force = {
      {1, 0.2, 0.33, 5}, {5, 1, 3, 9}, {3, 0.33, 1, 7}, {0.2, 0.11, 0.14, 1}};
  std::vector<std::vector<double>> matrix_criteria = {
      {1, 3, 5, 7}, {0.33, 1, 3, 5}, {0.2, 0.33, 1, 3}, {0.14, 0.2, 0.33, 1}};
  std::vector<std::vector<double>> matrix_result = {
      {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  for (auto i = 0; i < 4; ++i) {
    matrix_result[i][0] = (matrix_education[i][0] + matrix_education[i][1] +
                           matrix_education[i][2] + matrix_education[i][3]) /
                          37.31;
    matrix_result[i][1] = (matrix_character[i][0] + matrix_character[i][1] +
                           matrix_character[i][2] + matrix_character[i][3]) /
                          31.42;
    matrix_result[i][2] = (matrix_appearance[i][0] + matrix_appearance[i][1] +
                           matrix_appearance[i][2] + matrix_appearance[i][3]) /
                          36.56;
    matrix_result[i][3] = (matrix_force[i][0] + matrix_force[i][1] +
                           matrix_force[i][2] + matrix_force[i][3]) /
                          37.31;
  }
  std::vector<double> vec_criteria = {16 / 31.54, 9.33 / 31.54, 12.2 / 31.54,
                                      1.67 / 31.54};
  std::vector<double> estimated_vector =
      matrix_x_vector_task_4(matrix_result, vec_criteria);
  normalization_task_3(guys);
  boyfriend best_guy =
      choice_of_an_alternative_task3_task4(guys, estimated_vector);

  std::cout
      << "============================TASK4================================="
      << std::endl;
  print_matrix_task_4(matrix_education);
  print_matrix_task_4(matrix_character);
  print_matrix_task_4(matrix_appearance);
  print_matrix_task_4(matrix_force);
  print_matrix_task_4(matrix_criteria);
  print_vector_task_3_task_4(guys, estimated_vector);
  std::cout << "best_guy: " << best_guy.name << std::endl;
  std::cout
      << "=================================================================="
      << std::endl;
}

int main() {
  std::map<std::string, double> weights = {
      {"education", 8}, {"character", 6}, {"appearance", 4}, {"force", 2}};
  std::map<std::string, double> weights_normal = {{"education", 0.4},
                                                  {"character", 0.3},

                                                  {"appearance", 0.2},
                                                  {"force", 0.1}};
  boyfriend sergey("sergey", 7, 6, 4, 4);
  boyfriend aleksandr("aleksandr", 6, 6, 4, 6);
  boyfriend vladimir("vladimir", 3, 6, 7, 5);
  boyfriend anatoliy("anatoliy", 5, 3, 7, 2);
  vector_boyfriend guys(sergey, aleksandr, vladimir, anatoliy);
  task_1(guys);
  task_2(guys);
  task_3(guys, weights_normal);
  task_4(guys);

  return 0;
}
