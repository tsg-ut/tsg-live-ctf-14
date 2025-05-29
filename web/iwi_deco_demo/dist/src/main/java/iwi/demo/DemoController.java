package iwi.demo;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import org.apache.commons.lang3.StringUtils;
import org.springframework.web.bind.annotation.*;
import org.springframework.ui.Model;
import org.springframework.stereotype.Controller;

@Controller
public class DemoController {
  @GetMapping("/")
  public String home() {
    return "iwi_form";
  }

  @PostMapping("/profile")
  public String showProfile(@RequestParam("userId") String userId, Model model) {
    model.addAttribute("userId", userId);
    return "iwi_profile";
  }

  @GetMapping("/user/{userId}/settings")
  public String userSettings(@PathVariable String userId, Model model) {
    String lastLogin = LocalDateTime.now()
        .format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
    model.addAttribute("userId", userId);
    model.addAttribute("accountType", "Free");
    model.addAttribute("lastLogin", lastLogin);
    model.addAttribute("email", userId + "@example.com");
    model.addAttribute("description", "Please update your email.");
    return "iwi_user";
  }

  @PostMapping("/user/{userId}/settings")
  public String updateSettings(@PathVariable String userId,
      @RequestParam String email,
      @RequestParam String description,
      Model model) {
    String lastLogin = LocalDateTime.now()
        .format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));

    if (StringUtils.isBlank(email)) {
      model.addAttribute("message", "Email must not be blank.");
      email = userId + "@example.com";
    }

    if (StringUtils.isBlank(description)) {
      model.addAttribute("message", "Description is required.");
      description = "Please update your email.";
    }

    model.addAttribute("userId", userId);
    model.addAttribute("accountType", "Free");
    model.addAttribute("lastLogin", lastLogin);

    model.addAttribute("email", email);
    model.addAttribute("description", description);
    model.addAttribute("message", "Updated your profile.");

    return "iwi_user";
  }
}
